/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numutil.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:23:43 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 13:45:03 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMUTIL_H
# define NUMUTIL_H

# include <stdint.h>

uint16_t	read_u16_be(const void *buffer);

#endif // NUMUTIL_H