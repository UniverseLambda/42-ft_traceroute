/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:22:27 by clsaad            #+#    #+#             */
/*   Updated: 2023/09/04 10:39:35 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_H
# define BASE_H

# define START_PORT 33434

# define ST_TT_PRINT 0
# define ST_HOP_COUNT 1
# define ST_REACHED 2

# include <stdbool.h>
# include <netinet/in.h>

typedef struct in_addr	t_ip_addr;

typedef struct s_recv_time_inf
{
	uint64_t	rtt;
	t_ip_addr	addr;
	bool		reached;
}	t_recv_time_inf;

#endif // BASE_H
