/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:20:55 by clsaad            #+#    #+#             */
/*   Updated: 2023/09/04 17:23:32 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_H
# define CLI_H

# include <stdint.h>

# include "slice.h"

typedef struct s_cli
{
	const char	*host;
	uint16_t	max_ttl;
}	t_cli;

t_cli	cli(t_slice args);

#endif // CLI_H
