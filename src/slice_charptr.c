/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_charptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:38:55 by clsaad            #+#    #+#             */
/*   Updated: 2023/07/31 14:08:21 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/slice.h"

#include <stdio.h>

char	**slice_charptr(t_slice *self)
{
	return (slice_ptr(self));
}

char	*slice_charptr_get(t_slice *self, size_t index)
{
	if (index >= self->len)
	{
		fprintf(stderr,
			"slice_charptr_get: index out-of-bound (idx: %zu, len: %zu)",
			index, self->len);
	}
	return (slice_charptr(self)[index]);
}

void	slice_charptr_buildfrom(t_slice *self, t_fn_slice_cptr_bf fn, void *builder)
{
	size_t	index;

	index = 0;
	while (index < slice_len(self))
	{
		fn(builder, slice_charptr_get(self, index));
		++index;
	}
}
