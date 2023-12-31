/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_socket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:55:59 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 17:01:59 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SOCKET_H
# define FT_SOCKET_H

# include <stddef.h>

int		create_raw_socket(void);
int		create_udp_socket(int ttl);

void	set_socket_ttl(int fd, int ttl);
void	set_socket_timeout(int fd, size_t seconds, size_t micro);

#endif // FT_SOCKET_H
