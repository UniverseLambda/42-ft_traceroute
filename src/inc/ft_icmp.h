/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_icmp.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:13:29 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 16:46:21 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ICMP_H
# define FT_ICMP_H

# include <stdbool.h>
# include <stddef.h>
# include <netinet/in.h>

# include "resolve.h"

# define ICMP_INVALID_TYPE		0
# define ICMP_TTL_EXCEEDED		1
# define ICMP_PORT_UNREACHABLE	2

typedef struct s_icmp_res
{
	bool			valid;

	size_t			packet_type;
	struct in_addr	emitter;

	struct in_addr	target;
	int				src_port;
	int				dst_port;
}	t_icmp_res;

t_icmp_res	parse_icmp_resp(const char *buffer, size_t size,
				int start_port, int end_port);

#endif // FT_ICMP_H