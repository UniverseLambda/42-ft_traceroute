/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store_val.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:41:27 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 16:39:01 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_store.h"

t_store_val	storev_uint(size_t v)
{
	return ((t_store_val){.uint = v});
}

t_store_val	storev_sint(ssize_t v)
{
	return ((t_store_val){.sint = v});
}

t_store_val	storev_ptr(void *v)
{
	return ((t_store_val){.ptr = v});
}

t_store_val	storev_zero(void)
{
	return ((t_store_val){.uint = 0});
}
