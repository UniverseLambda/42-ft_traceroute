/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:06:30 by clsaad            #+#    #+#             */
/*   Updated: 2023/07/31 15:33:46 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/slice.h"
#include <stdio.h>

t_slice	slice_new(void *ptr, size_t len)
{
	return ((t_slice){.ptr = ptr, .len = len});
}

void	*slice_ptr(t_slice *self)
{
	return (self->ptr);
}

size_t	slice_len(t_slice *self)
{
	return (self->len);
}
