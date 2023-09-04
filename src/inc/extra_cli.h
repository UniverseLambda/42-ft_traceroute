/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_cli.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:09:19 by clsaad            #+#    #+#             */
/*   Updated: 2023/09/04 17:06:08 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRA_CLI_H
# define EXTRA_CLI_H

# include <stdint.h>
# include <stddef.h>

enum e_builder_state
{
	CLI_EMPTY = 0,
	CLI_MAX_TTL = 1
};

struct	s_cli_builder
{
	char					*host;
	uint16_t				max_ttl;
	enum e_builder_state	state;
	size_t					index;
};

void	cli_handle_state(struct s_cli_builder *builder, char *arg);

#endif // EXTRA_CLI_H
