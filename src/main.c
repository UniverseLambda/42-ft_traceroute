/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:30:51 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/02 16:51:26 by clsaad           ###   ########.fr       */
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

#define START_PORT 44343

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

static void	print_time(t_resp_inf resp, uint64_t *receive_time, size_t *receive_time_offset, bool timeout)
{
	static size_t	hop_count = 0;

	while (*receive_time_offset < resp.count)
	{
		if (receive_time[*receive_time_offset])
		{
			if (!((*receive_time_offset + resp.hop_offset) % 3))
			{
				if (*receive_time_offset + resp.hop_offset)
					printf("\n");
				printf(" %lu", ++hop_count);
			}
			printf("  %.3f ms", (double)(receive_time[*receive_time_offset]) / 1000);
		}
		else
		{
			if (!timeout)
				break ;
			if (!((*receive_time_offset + resp.hop_offset) % 3))
			{
				if (*receive_time_offset + resp.hop_offset)
					printf("\n");
				printf(" %lu", ++hop_count);
			}
			printf("  *");
		}
		*receive_time_offset += 1;
	}
}

static void	handle_response(t_resp_inf resp, size_t buffer_len, uint64_t *receive_time)
{
	const uint64_t		received = now_micro();
	const int			port_end = resp.window_port_start + resp.count;
	const t_icmp_res	icmp_res = parse_icmp_resp(resp.buffer, buffer_len, resp.window_port_start, port_end);

	(void)receive_time;
	if (!icmp_res.valid)
		return ;
	// printf("RESPONSE: FROM %s", inet_ntoa(icmp_res.emitter));
	// printf("(orig src_port: %d, dst: %s:%d)\n", icmp_res.src_port, inet_ntoa(icmp_res.target), icmp_res.dst_port);
	receive_time[icmp_res.dst_port - resp.window_port_start] = received - resp.sent_time;

}

static void	listen_response(int raw_socket, t_window window_start, size_t count)
{
	char				buffer[512];
	ssize_t				buffer_len;
	const t_resp_inf	resp_inf = (t_resp_inf){now_micro(), START_PORT + (3 * window_start.start_hop) + window_start.hop_offset, buffer, count, window_start.hop_offset};
	uint64_t			receive_time[count];
	size_t				receive_time_offset;

	ft_memset(buffer, 0, sizeof(buffer));
	ft_memset(receive_time, 0, sizeof(uint64_t) * count);
	receive_time_offset = 0;
	while (1)
	{
		buffer_len = recvfrom(raw_socket, &buffer, sizeof(buffer), 0, NULL, NULL);
		if (buffer_len > 0)
		{
			handle_response(resp_inf, (size_t)buffer_len, receive_time);
			print_time(resp_inf, receive_time, &receive_time_offset, false);
		}
		if (now_micro() - resp_inf.sent_time >= 5000000)
			break;
	}
	print_time(resp_inf, receive_time, &receive_time_offset, true);
	printf("\n");

}

static void	loop(int udp_socket, int raw_socket, t_sockaddr_res addr)
{
	size_t		iter_sent;
	t_window	current_window;
	t_window	previous_window;

	ft_memset(&current_window, 0, sizeof(current_window));
	ft_memset(&previous_window, 0, sizeof(previous_window));
	while (current_window.start_hop < 30)
	{
		iter_sent = 0;
		while (iter_sent++ < 16 && current_window.start_hop < 30)
		{
			((struct sockaddr_in *)&addr.sock_addr)->sin_port += ntohs(1);
			set_socket_ttl(udp_socket, (int)current_window.start_hop + 1);
			if (sendto(udp_socket, "ZARMAPIPOUDOU69", 15, 0, &addr.sock_addr, addr.sock_addr_len) == -1)
				ft_perror("sendto");
			if (++current_window.hop_offset == 3)
			{
				current_window.start_hop += 1;
				current_window.hop_offset = 0;
			}
		}
		listen_response(raw_socket, previous_window, iter_sent - 1);
		previous_window = current_window;
	}
}

int main(int argc, char **argv)
{
	char			*target;
	t_sockaddr_res	sockaddr;
	int				udp_socket;
	int				raw_socket;

	target = cli(slice_new(argv + 1, argc - 1));
	sockaddr = select_interface(target);
	udp_socket = create_udp_socket();
	raw_socket = create_raw_socket();
	set_socket_timeout(raw_socket, 0, 10000);
	((struct sockaddr_in *)&sockaddr.sock_addr)->sin_port = ntohs(START_PORT);
	loop(udp_socket, raw_socket, sockaddr);
	close(udp_socket);
	close(raw_socket);
	return (0);
}
