/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numutil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:19:24 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 13:45:40 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/numutil.h"

#include <stdint.h>

uint16_t	read_u16_be(const void *buffer)
{
	const uint8_t	*bbuffer = buffer;

	return (((uint16_t)bbuffer[0]) << 8 | bbuffer[1]);
}
