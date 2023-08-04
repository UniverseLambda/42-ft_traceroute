/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:30:51 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 15:35:42 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

#include "inc/cli.h"
#include "inc/resolve.h"
#include "inc/ft_stdutil.h"
#include "inc/ft_socket.h"
#include "inc/ft_time.h"
#include "inc/ft_icmp.h"
#include "inc/ft_store.h"

#define START_PORT 33434

#define ST_TT_PRINT 0
#define ST_HOP_COUNT 1
#define ST_REACHED 2

typedef	struct s_window
{
	size_t	start_hop;
	size_t	hop_offset;
}	t_window;

typedef struct s_response_info
{
	uint64_t	sent_time;
	uint64_t	window_port_start;
	char		*buffer;
	size_t		count;
	size_t		hop_offset;
} t_resp_inf;

typedef struct s_recv_time_inf
{
	uint64_t		rtt;
	struct in_addr	addr;
	bool			reached;
}	t_recv_time_inf;

static bool	print_time(t_resp_inf resp, t_recv_time_inf *receive_time, size_t *receive_time_offset, bool timeout)
{
	static struct in_addr	last_address;
	t_recv_time_inf 		*curr;

	while (*receive_time_offset < resp.count)
	{
		curr = receive_time + *receive_time_offset;
		if (!timeout && curr->rtt == 0)
			break ;
		if ((store_get(ST_TT_PRINT).uint % 3) == 0)
		{
			if (store_get(ST_REACHED).uint)
				return (true);
			ft_memset(&last_address, 0, sizeof(last_address));
			printf("%2lu", store_add(ST_HOP_COUNT, storev_uint(1)).uint);
		}
		if (curr->rtt != 0)
		{
			if (ft_memcmp(&last_address, &(curr->addr), sizeof(last_address)))
				printf("  %s", inet_ntoa(curr->addr));
			printf("  %.3f ms", (double)(curr->rtt) / 1000.0);
			ft_memcpy(&last_address, &(curr->addr), sizeof(last_address));
			store_cmpxchg(ST_REACHED, storev_zero(), storev_uint(curr->reached));
		}
		else
			printf("  *");
		store_add(ST_TT_PRINT, storev_uint(1));
		*receive_time_offset += 1;
		if (store_get(ST_TT_PRINT).uint && store_get(ST_TT_PRINT).uint % 3 == 0)
			printf("\n");
	}
	return (false);
}

static void	handle_response(t_resp_inf resp, size_t buffer_len, t_recv_time_inf *receive_time)
{
	const uint64_t		received = now_micro();
	const int			port_end = resp.window_port_start + resp.count;
	const t_icmp_res	icmp_res = parse_icmp_resp(resp.buffer, buffer_len, resp.window_port_start, port_end);
	const size_t		idx = icmp_res.dst_port - resp.window_port_start;

	if (!icmp_res.valid)
		return ;
	receive_time[idx].rtt = received - resp.sent_time;
	receive_time[idx].addr = icmp_res.emitter;
	receive_time[idx].reached = icmp_res.icmp_packet_type == ICMP_PORT_UNREACHABLE;
}

static bool	listen_response(int raw_socket, t_window window_start, size_t count)
{
	char				buffer[512];
	ssize_t				buffer_len;
	const t_resp_inf	resp_inf = (t_resp_inf){now_micro(), START_PORT + (3 * window_start.start_hop) + window_start.hop_offset, buffer, count, window_start.hop_offset};
	t_recv_time_inf		receive_time[count];
	size_t				receive_time_offset;

	ft_memset(buffer, 0, sizeof(buffer));
	ft_memset(receive_time, 0, sizeof(t_recv_time_inf) * count);
	receive_time_offset = 0;
	while (receive_time_offset < count)
	{
		buffer_len = recvfrom(raw_socket, &buffer, sizeof(buffer), MSG_WAITALL, NULL, NULL);
		if (buffer_len > 0)
		{
			handle_response(resp_inf, (size_t)buffer_len, receive_time);
			if (print_time(resp_inf, receive_time, &receive_time_offset, false))
				return (true);
		}
		if (now_micro() - resp_inf.sent_time >= 5000000)
			break;
	}
	return (print_time(resp_inf, receive_time, &receive_time_offset, true));
}

static void	loop(int raw_socket, t_sockaddr_res addr)
{
	size_t		iter_sent;
	t_window	current_window;
	t_window	previous_window;
	int			udp_socket;

	ft_memset(&current_window, 0, sizeof(current_window));
	ft_memset(&previous_window, 0, sizeof(previous_window));
	while (current_window.start_hop < 30)
	{
		iter_sent = 0;
		while (iter_sent++ < 16 && current_window.start_hop < 30)
		{
			udp_socket = create_udp_socket();
			set_socket_ttl(udp_socket, (int)current_window.start_hop + 1);
			if (sendto(udp_socket, "ZARMAPIPOUDOU69", 15, 0, &addr.sock_addr, addr.sock_addr_len) == -1)
				ft_perror("sendto");
			close(udp_socket);
			if (++current_window.hop_offset == 3)
			{
				current_window.start_hop += 1;
				current_window.hop_offset = 0;
			}
			((struct sockaddr_in *)&addr.sock_addr)->sin_port += ntohs(1);
		}
		if (listen_response(raw_socket, previous_window, iter_sent - 1))
			break ;
		previous_window = current_window;
	}
}

int main(int argc, char **argv)
{
	char				*target;
	t_sockaddr_res		sockaddr;
	struct sockaddr_in	*addr_in;
	int					raw_socket;

	target = cli(slice_new(argv + 1, argc - 1));
	sockaddr = select_interface(target);
	addr_in = (struct sockaddr_in *)&sockaddr.sock_addr;
	raw_socket = create_raw_socket();
	set_socket_timeout(raw_socket, 0, 100000);
	addr_in->sin_port = ntohs(START_PORT);
	printf("traceroute to %s (%s), 30 hops max, 15 byte packets\n", target, inet_ntoa(addr_in->sin_addr));
	loop(raw_socket, sockaddr);
	close(raw_socket);
	return (0);
}
