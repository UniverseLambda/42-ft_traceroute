/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:38:55 by clsaad            #+#    #+#             */
/*   Updated: 2023/07/31 14:11:48 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/slice.h"

#include <stdio.h>

char	*slice_char(t_slice *self)
{
	return (slice_ptr(self));
}

char	slice_char_get(t_slice *self, size_t index)
{
	if (index >= self->len)
	{
		fprintf(stderr,
			"slice_char_get: index out-of-bound (idx: %zu, len: %zu)",
			index, self->len);
	}
	return (slice_char(self)[index]);
}

void	slice_char_buildfrom(t_slice *self, t_fn_slice_c_bf fn, void *builder)
{
	size_t	index;

	index = 0;
	while (index < slice_len(self))
	{
		fn(builder, slice_char_get(self, index));
		++index;
	}
}

t_slice	slice_char_from_cstr(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
	{
		++len;
	}
	return (slice_new(str, len));
}
