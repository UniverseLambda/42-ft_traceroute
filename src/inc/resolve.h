/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:28:36 by clsaad            #+#    #+#             */
/*   Updated: 2023/07/31 17:30:58 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOLVE_H
# define RESOLVE_H

# include <stddef.h>
# include <stdbool.h>
# include <sys/socket.h>

typedef struct s_sockaddr_res
{
	struct sockaddr	sock_addr;
	size_t			sock_addr_len;
	bool			is_valid;
}	t_sockaddr_res;

t_sockaddr_res	select_interface(char *address);

#endif // RESOLVE_H
