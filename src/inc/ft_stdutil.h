/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdutil.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:25:49 by clsaad            #+#    #+#             */
/*   Updated: 2023/07/31 14:34:52 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDUTIL_H
# define FT_STDUTIL_H

# include <unistd.h>

void	*ft_memset(void *dest, int v, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

int		ft_strcmp(const char *s1, const char *s2);

#endif // FT_STDUTIL_H