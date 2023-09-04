/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:37:30 by clsaad            #+#    #+#             */
/*   Updated: 2023/09/04 10:58:06 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_TIME_H
# define PRINT_TIME_H

# include <stdbool.h>
# include <stddef.h>

# include "base.h"
# include "resp_inf.h"

bool	print_time(t_resp_inf resp, t_recv_time_inf *receive_time,
			size_t *receive_time_offset, bool timeout);

#endif // PRINT_TIME_H