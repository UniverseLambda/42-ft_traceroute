/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdutil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:26:44 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/01 15:29:36 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_stdutil.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

void	*ft_memset(void *dest, int v, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = (char)v;
		++i;
	}
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		++i;
	}
	return (dest);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				index;
	const unsigned char	*c1 = s1;
	const unsigned char	*c2 = s2;

	if (s1 == s2)
		return (0);
	index = 0;
	while (index < n)
	{
		if (c1[index] != c2[index])
		{
			return (c1[index] - c2[index]);
		}
		++index;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*us1 = (unsigned char *)s1;
	const unsigned char	*us2 = (unsigned char *)s2;
	size_t				index;

	index = 0;
	if (s1 == s2)
		return (0);
	while (us1[index] == us2[index] && us1[index] != '\0')
		++index;
	return (us1[index] - us2[index]);
}

void ft_perror(const char *action)
{
	fprintf(stderr, "ft_traceroute: %s: %s\n", action, strerror(errno));
}
