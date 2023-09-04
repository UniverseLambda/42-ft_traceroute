/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:28:36 by clsaad            #+#    #+#             */
/*   Updated: 2023/09/04 17:27:39 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOLVE_H
# define RESOLVE_H

# include <stddef.h>
# include <stdbool.h>
# include <sys/socket.h>

# include "base.h"

typedef struct s_sockaddr_res
{
	struct sockaddr	sock_addr;
	size_t			sock_addr_len;
	bool			is_valid;
}	t_sockaddr_res;

t_sockaddr_res	select_interface(const char *address);
char			*resolve_cache_addr(const t_ip_addr *sockaddr);

#endif // RESOLVE_H
