/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_cli.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:09:07 by clsaad            #+#    #+#             */
/*   Updated: 2023/09/04 17:22:21 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/extra_cli.h"

#include <stdio.h>
#include <stdlib.h>

__attribute__ ((__noreturn__))
static void	invalid_arg(size_t idx, char *arg)
{
	idx += 1;
	fprintf(stderr,
		"Invalid arg `%s' (position %zu, argc %zu)\n",
		arg,
		idx,
		idx);
	exit(2);
}

static int32_t	parse_number(char *arg)
{
	uint32_t	res;

	res = 0;
	if (!arg[0])
		return (-1);
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
			return (-1);
		res = (res * 10) + (*arg - '0');
		if (res > UINT16_MAX)
			return (-1);
		++arg;
	}
	return ((int32_t)res);
}

static void	handle_max_ttl(struct s_cli_builder *builder, char *arg)
{
	const int32_t	res = parse_number(arg);

	if (res <= 0)
		invalid_arg(builder->index, arg);
	builder->max_ttl = (uint16_t)res;
}

void	cli_handle_state(struct s_cli_builder *builder, char *arg)
{
	if (builder->state == CLI_MAX_TTL)
		handle_max_ttl(builder, arg);
	builder->state = CLI_EMPTY;
}
