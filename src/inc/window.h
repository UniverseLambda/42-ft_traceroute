/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:17:46 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 17:18:35 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <stddef.h>

typedef struct s_window
{
	size_t	start_hop;
	size_t	hop_offset;
}	t_window;

void	inc_window(t_window	*window);

#endif // WINDOW_H
