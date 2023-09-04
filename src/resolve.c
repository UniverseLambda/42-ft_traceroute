/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:26:24 by clsaad            #+#    #+#             */
/*   Updated: 2023/09/04 17:27:49 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/resolve.h"

#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

#include "inc/ft_stdutil.h"

static struct addrinfo	*resolve_host(const char *host)
{
	struct addrinfo	hints;
	struct addrinfo	*result;
	int				gai_ret_val;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	gai_ret_val = getaddrinfo(host, NULL, &hints, &result);
	if (gai_ret_val != 0)
	{
		fprintf(stderr,
			"ft_traceroute: %s: %s\n", host, gai_strerror(gai_ret_val));
		return (NULL);
	}
	return (result);
}

t_sockaddr_res	select_interface(const char *address)
{
	struct addrinfo	*current;
	struct addrinfo	*resolved;
	struct sockaddr	selected_address;
	size_t			selected_addresslen;

	selected_address = (struct sockaddr){0};
	selected_addresslen = 0;
	resolved = resolve_host(address);
	if (resolved == NULL)
		return ((t_sockaddr_res){0});
	current = resolved;
	while (current != NULL)
	{
		if (current->ai_addr && current->ai_addrlen > 0)
		{
			selected_address = *(current->ai_addr);
			selected_addresslen = current->ai_addrlen;
			break ;
		}
		current = current->ai_next;
	}
	if (!current)
		return ((t_sockaddr_res){0});
	freeaddrinfo(resolved);
	return ((t_sockaddr_res){selected_address, selected_addresslen, true});
}

char	*resolve_cache_addr(const t_ip_addr *sockaddr)
{
	static struct sockaddr_in	last_addr;
	static char					buf[257];

	if (sockaddr->s_addr == last_addr.sin_addr.s_addr)
		return (buf);
	last_addr.sin_addr = *sockaddr;
	last_addr.sin_family = AF_INET;
	buf[0] = '\0';
	getnameinfo((const struct sockaddr *)&last_addr, sizeof(last_addr),
		buf, sizeof(buf), NULL, 0, 0);
	return (buf);
}
