/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:00:21 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 16:32:44 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLICE_H
# define SLICE_H

# include <stddef.h>

typedef struct s_slice
{
	void	*ptr;
	size_t	len;
}	t_slice;

t_slice	slice_new(void *ptr, size_t len);
void	*slice_ptr(t_slice *self);
size_t	slice_len(t_slice *self);

// char *

typedef	void (t_fn_slice_cptr_bf)(void *builder, char *value);

char	**slice_charptr(t_slice *self);
char	*slice_charptr_get(t_slice *self, size_t index);
void	slice_charptr_buildfrom(t_slice *self, t_fn_slice_cptr_bf fn,
			void *builder);

// char

typedef void (t_fn_slice_c_bf)(void *builder, char value);

char	*slice_char(t_slice *self);
char	slice_char_get(t_slice *self, size_t index);
void	slice_char_buildfrom(t_slice *self, t_fn_slice_c_bf fn, void *builder);
t_slice	slice_char_from_cstr(char *str);

#endif // SLICE_H
