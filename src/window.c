/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:17:22 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 17:18:55 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/window.h"

void	inc_window(t_window	*window)
{
	window->hop_offset += 1;
	if (window->hop_offset == 3)
	{
		window->start_hop += 1;
		window->hop_offset = 0;
	}
}
