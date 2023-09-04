/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resp_inf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:17:22 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 17:23:10 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/resp_inf.h"

#include "inc/base.h"
#include "inc/ft_time.h"

t_resp_inf	new_resp_inf(t_window win, size_t count, char *buf)
{
	t_resp_inf	res;

	res.sent_time = now_micro();
	res.window_port_start = START_PORT + (3 * win.start_hop)
		+ win.hop_offset;
	res.buffer = buf;
	res.count = count;
	res.hop_offset = win.hop_offset;
	return (res);
}
