/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:17:08 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 16:42:13 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STORE_H
# define FT_STORE_H

# include <stddef.h>
# include <sys/types.h>
# include <stdbool.h>

typedef union u_store_val
{
	size_t	uint;
	ssize_t	sint;
	void	*ptr;
}	t_store_val;

t_store_val	store_get(size_t slot);
t_store_val	store_set(size_t slot, t_store_val val);
t_store_val	*store_ptr(size_t slot);
bool		store_cmpswp(size_t slot, t_store_val old, t_store_val new);
t_store_val	store_add(size_t slot, t_store_val val);

t_store_val	storev_uint(size_t v);
t_store_val	storev_sint(ssize_t v);
t_store_val	storev_ptr(void *v);
t_store_val	storev_zero(void);

#endif // FT_STORE_H
