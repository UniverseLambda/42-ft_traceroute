/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:32:27 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/01 16:12:09 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H

# include <stdint.h>

uint64_t	now_micro(void);
uint64_t	now_sec(void);
uint64_t	now_timestamp(void);
uint64_t	micro_from_timestamp(uint64_t timestamp);

#endif // FT_TIME_H