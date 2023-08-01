/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:30:51 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/01 15:43:53 by clsaad           ###   ########.fr       */
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

// static void listen_response(int raw_socket, size_t start_hop, size_t hop_offset, size_t count)
// {

// }

static void	loop(int udp_socket, int raw_socket, t_sockaddr_res addr)
{
	size_t	iter_sent;
	size_t	sent_hop;
	size_t	last_hop_sent;

	(void)raw_socket;
	sent_hop = 0;
	last_hop_sent = 0;
	while (sent_hop < 30)
	{
		iter_sent = 0;
		while (iter_sent < 16 && sent_hop < 30)
		{
			((struct sockaddr_in *)&addr.sock_addr)->sin_port += ntohs(1);
			set_socket_ttl(udp_socket, (int)sent_hop + 1);
			if (sendto(udp_socket, "ZARMAPIPOUDOU69", 15, 0, &addr.sock_addr, addr.sock_addr_len) == -1)
				ft_perror("sendto");
			if (++last_hop_sent == 3)
			{
				sent_hop += 1;
				last_hop_sent = 0;
			}
		}
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
	set_socket_timeout(raw_socket, 5, 0);
	((struct sockaddr_in *)&sockaddr.sock_addr)->sin_port = ntohs(44343);
	loop(udp_socket, raw_socket, sockaddr);
	close(udp_socket);
	close(raw_socket);
	return (0);
}
