/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:30:51 by clsaad            #+#    #+#             */
/*   Updated: 2023/09/04 17:26:56 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "inc/base.h"
#include "inc/cli.h"
#include "inc/ft_icmp.h"
#include "inc/ft_socket.h"
#include "inc/ft_stdutil.h"
#include "inc/ft_store.h"
#include "inc/ft_time.h"
#include "inc/print_time.h"
#include "inc/resolve.h"
#include "inc/resp_inf.h"
#include "inc/window.h"

static void	handle_response(t_resp_inf resp, size_t buf_len,
				t_recv_time_inf *receive_time)
{
	const uint64_t	received = now_micro();
	const int		port_end = resp.window_port_start + resp.count;
	t_icmp_res		res;
	size_t			idx;

	res = parse_icmp_resp(resp.buffer, buf_len,
			resp.window_port_start, port_end);
	idx = res.dst_port - resp.window_port_start;
	if (!res.valid)
		return ;
	receive_time[idx].rtt = received - resp.sent_time;
	receive_time[idx].addr = res.emitter;
	receive_time[idx].reached = res.packet_type == ICMP_PORT_UNREACHABLE;
}

static bool	listen_response(int raw_socket, t_window window_start, size_t count)
{
	char			buffer[512];
	ssize_t			buffer_len;
	t_resp_inf		resp_inf;
	t_recv_time_inf	receive_time[32];
	size_t			receive_time_offset;

	resp_inf = new_resp_inf(window_start, count, buffer);
	ft_memset(buffer, 0, sizeof(buffer));
	ft_memset(receive_time, 0, sizeof(t_recv_time_inf) * count);
	receive_time_offset = 0;
	while (receive_time_offset < count)
	{
		buffer_len = recvfrom(raw_socket,
				&buffer, sizeof(buffer), MSG_WAITALL, NULL, NULL);
		if (buffer_len > 0)
			handle_response(resp_inf, (size_t)buffer_len, receive_time);
		if (now_micro() - resp_inf.sent_time >= 5000000)
			break ;
	}
	return (print_time(resp_inf, receive_time, &receive_time_offset, true));
}

static void	loop(int raw_socket, t_sockaddr_res addr, uint16_t max_ttl)
{
	size_t		iter_sent;
	t_window	current_window;
	t_window	previous_window;
	int			udp_socket;

	ft_memset(&current_window, 0, sizeof(current_window));
	ft_memset(&previous_window, 0, sizeof(previous_window));
	while (current_window.start_hop < max_ttl)
	{
		iter_sent = 0;
		while (iter_sent++ < 16 && current_window.start_hop < max_ttl)
		{
			udp_socket = create_udp_socket((int)current_window.start_hop + 1);
			if (sendto(udp_socket, "ZARMAPIPOUDOU69", 15, 0,
					&addr.sock_addr, addr.sock_addr_len) == -1)
				ft_perror("sendto");
			close(udp_socket);
			inc_window(&current_window);
			((struct sockaddr_in *)&addr.sock_addr)->sin_port += ntohs(1);
		}
		if (listen_response(raw_socket, previous_window, iter_sent - 1))
			break ;
		previous_window = current_window;
	}
}

int	main(int argc, char **argv)
{
	t_cli				conf;
	t_sockaddr_res		sockaddr;
	struct sockaddr_in	*addr_in;
	int					raw_socket;

	conf = cli(slice_new(argv + 1, argc - 1));
	sockaddr = select_interface(conf.host);
	if (!sockaddr.is_valid)
		exit(2);
	addr_in = (struct sockaddr_in *)&sockaddr.sock_addr;
	raw_socket = create_raw_socket();
	set_socket_timeout(raw_socket, 0, 100000);
	addr_in->sin_port = ntohs(START_PORT);
	printf("traceroute to %s (%s), %u hops max, 15 byte packets\n",
		conf.host, inet_ntoa(addr_in->sin_addr), conf.max_ttl);
	loop(raw_socket, sockaddr, conf.max_ttl);
	close(raw_socket);
	return (0);
}
