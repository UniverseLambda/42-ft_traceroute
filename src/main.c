/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:30:51 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 13:32:11 by clsaad           ###   ########.fr       */
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

#define START_PORT 33434

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
}	t_recv_time_inf;

static void	print_time(t_resp_inf resp, t_recv_time_inf *receive_time, size_t *receive_time_offset, bool timeout)
{
	static size_t			total_printed = 0;
	static size_t			hop_count = 0;
	static struct in_addr	last_address;
	bool					is_looping;

	while (*receive_time_offset < resp.count)
	{
		is_looping = timeout || receive_time[*receive_time_offset].rtt != 0;
		if (!is_looping)
			break ;
		if ((total_printed % 3) == 0)
		{
			ft_memset(&last_address, 0, sizeof(last_address));
			printf("%2lu", ++hop_count);
		}
		if (receive_time[*receive_time_offset].rtt != 0)
		{
			if (ft_memcmp(&last_address, &(receive_time[*receive_time_offset].addr), sizeof(last_address)))
				printf("  %s", inet_ntoa(receive_time[*receive_time_offset].addr));
			printf("  %.3f ms", (double)(receive_time[*receive_time_offset].rtt) / 1000.0);
			ft_memcpy(&last_address, &(receive_time[*receive_time_offset].addr), sizeof(last_address));
		}
		else if (timeout)
			printf("  *");
		total_printed += is_looping;
		*receive_time_offset += is_looping;
		if (total_printed && total_printed % 3 == 0)
			printf("\n");
	}
}

static void	handle_response(t_resp_inf resp, size_t buffer_len, t_recv_time_inf *receive_time)
{
	const uint64_t		received = now_micro();
	const int			port_end = resp.window_port_start + resp.count;
	const t_icmp_res	icmp_res = parse_icmp_resp(resp.buffer, buffer_len, resp.window_port_start, port_end);

	if (!icmp_res.valid)
		return ;
	receive_time[icmp_res.dst_port - resp.window_port_start].rtt = received - resp.sent_time;
	receive_time[icmp_res.dst_port - resp.window_port_start].addr = icmp_res.emitter;
	// icmp_res.
}

static void	listen_response(int raw_socket, t_window window_start, size_t count)
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
			print_time(resp_inf, receive_time, &receive_time_offset, false);
		}
		if (now_micro() - resp_inf.sent_time >= 5000000)
			break;
	}
	print_time(resp_inf, receive_time, &receive_time_offset, true);
}

static void	loop(/* int udp_socket, */int raw_socket, t_sockaddr_res addr)
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
		listen_response(raw_socket, previous_window, iter_sent - 1);
		previous_window = current_window;
	}
}

int main(int argc, char **argv)
{
	char				*target;
	t_sockaddr_res		sockaddr;
	struct sockaddr_in	*addr_in;
	// int					udp_socket;
	int					raw_socket;

	target = cli(slice_new(argv + 1, argc - 1));
	sockaddr = select_interface(target);
	addr_in = (struct sockaddr_in *)&sockaddr.sock_addr;
	// udp_socket = create_udp_socket();
	raw_socket = create_raw_socket();
	set_socket_timeout(raw_socket, 0, 100000);
	addr_in->sin_port = ntohs(START_PORT);
	printf("traceroute to %s (%s), 30 hops max, 15 byte packets\n", target, inet_ntoa(addr_in->sin_addr));
	loop(/* udp_socket, */ raw_socket, sockaddr);
	// close(udp_socket);
	close(raw_socket);
	return (0);
}
