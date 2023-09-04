/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:37:09 by clsaad            #+#    #+#             */
/*   Updated: 2023/09/04 10:49:09 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/print_time.h"

#include <arpa/inet.h>
#include <stdio.h>

#include "inc/base.h"
#include "inc/ft_store.h"
#include "inc/ft_stdutil.h"

static void	print_no_timeout(t_ip_addr *last_address, t_recv_time_inf *curr)
{
	if (ft_memcmp(last_address, &(curr->addr), sizeof(*last_address)))
		printf("  %s", inet_ntoa(curr->addr));
	printf("  %.3f ms", (double)(curr->rtt) / 1000.0);
	ft_memcpy(last_address, &(curr->addr), sizeof(*last_address));
	store_cmpswp(ST_REACHED, storev_zero(), storev_uint(curr->reached));
}

bool	print_time(t_resp_inf resp, t_recv_time_inf *receive_time,
						size_t *receive_time_offset, bool timeout)
{
	static t_ip_addr	last_address;
	t_recv_time_inf		*curr;

	while (*receive_time_offset < resp.count)
	{
		curr = receive_time + *receive_time_offset;
		if (!timeout && curr->rtt == 0)
			break ;
		if ((store_get(ST_TT_PRINT).uint % 3) == 0)
		{
			if (store_get(ST_REACHED).uint)
				return (true);
			ft_memset(&last_address, 0, sizeof(last_address));
			printf("%2lu", store_add(ST_HOP_COUNT, storev_uint(1)).uint);
		}
		if (curr->rtt != 0)
			print_no_timeout(&last_address, curr);
		else
			printf("  *");
		store_add(ST_TT_PRINT, storev_uint(1));
		*receive_time_offset += 1;
		if (store_get(ST_TT_PRINT).uint && store_get(ST_TT_PRINT).uint % 3 == 0)
			printf("\n");
	}
	return (false);
}
