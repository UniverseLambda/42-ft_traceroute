/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:30:50 by clsaad            #+#    #+#             */
/*   Updated: 2023/09/05 11:23:12 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cli.h"

#include <stdio.h>
#include <stdlib.h>

#include "inc/ft_stdutil.h"
#include "inc/extra_cli.h"

__attribute__ ((__noreturn__))
static void	usage(void)
{
	fprintf(stderr, "Usage:\n  traceroute [ -m max_ttl ] host\nOptions:\n");
	fprintf(stderr, "  -m max_ttl  --max-hops=max_ttl\n");
	fprintf(stderr, "                              Set the max number of hops"
		"(max TTL to be\n");
	fprintf(stderr, "                              reached). Default is 30\n");
	fprintf(stderr, "  --help                      Read this help and exit\n");
	fprintf(stderr, "Arguments:\n");
	fprintf(stderr, "+     host          The host to traceroute to\n");
	exit(0);
}

__attribute__ ((__noreturn__))
static void	bad_option(size_t idx, char *option)
{
	idx += 1;
	fprintf(stderr, "Bad option `%s' (argc %zu)\n", option, idx);
	exit(2);
}

__attribute__ ((__noreturn__))
static void	extra_arg(size_t idx, char *host)
{
	idx += 1;
	fprintf(stderr,
		"Extra arg `%s' (position %zu, argc %zu)\n",
		host,
		idx,
		idx);
	exit(2);
}

static void	build_from(struct s_cli_builder *builder, char *arg)
{
	if (builder->state != CLI_EMPTY)
		cli_handle_state(builder, arg);
	else if (arg[0] == '-')
	{
		if (ft_strcmp(arg, "--help") == 0)
			usage();
		else if (ft_strcmp(arg, "-m") == 0)
			builder->state = CLI_MAX_TTL;
		else
			bad_option(builder->index, arg);
	}
	else
	{
		if (builder->host != NULL)
			extra_arg(builder->index, arg);
		builder->host = arg;
	}
	builder->index += 1;
}

t_cli	cli(t_slice args)
{
	struct s_cli_builder	builder;
	t_cli					result;

	ft_memset(&builder, 0, sizeof(builder));
	builder.max_ttl = 30;
	slice_charptr_buildfrom(&args, (void *)build_from, &builder);
	if (builder.state != CLI_EMPTY)
	{
		fprintf(stderr, "Missing argument (argc %zu)\n", builder.index);
		exit(2);
	}
	if (builder.host == NULL)
		usage();
	result.host = builder.host;
	result.max_ttl = builder.max_ttl;
	return (result);
}
