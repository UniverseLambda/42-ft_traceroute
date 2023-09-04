/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:22:36 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 16:42:13 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_store.h"

t_store_val	store_get(size_t slot)
{
	return (*store_ptr(slot));
}

t_store_val	store_set(size_t slot, t_store_val val)
{
	*store_ptr(slot) = val;
	return (val);
}

t_store_val	*store_ptr(size_t slot)
{
	static t_store_val	global_store[512];

	return (&global_store[slot]);
}

bool	store_cmpswp(size_t slot, t_store_val old, t_store_val new)
{
	t_store_val	*slot_ptr;

	slot_ptr = store_ptr(slot);
	if (slot_ptr->uint == old.uint)
	{
		*slot_ptr = new;
		return (true);
	}
	return (false);
}

t_store_val	store_add(size_t slot, t_store_val val)
{
	store_ptr(slot)->uint += val.uint;
	return (*store_ptr(slot));
}
