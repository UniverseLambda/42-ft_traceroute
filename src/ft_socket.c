/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_socket.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:36:50 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/01 15:40:16 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>

#include "inc/ft_stdutil.h"

int	create_raw_socket()
{
	int	fd;

	fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd == -1)
		ft_perror("socket");
	return (fd);
}

int	create_udp_socket()
{
	int					fd;

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1)
		ft_perror("socket");
	return (fd);
}

void	set_socket_ttl(int fd, int ttl)
{
	if (setsockopt(fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) == -1)
		ft_perror("set_socket_ttl");
}

void	set_socket_timeout(int fd, size_t seconds, size_t micro)
{
	struct timeval	tv;

	tv.tv_sec = (time_t)seconds;
	tv.tv_usec = (suseconds_t)micro;
	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == -1)
		ft_perror("set_socket_timeout");
}
