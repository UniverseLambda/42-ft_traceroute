/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resp_inf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:17:46 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 17:21:43 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESP_INF_H
# define RESP_INF_H

# include <stddef.h>
# include <stdint.h>

# include "window.h"

typedef struct s_response_info
{
	uint64_t	sent_time;
	uint64_t	window_port_start;
	char		*buffer;
	size_t		count;
	size_t		hop_offset;
}	t_resp_inf;

t_resp_inf	new_resp_inf(t_window win, size_t count, char *buf);

#endif // RESP_INF_H
