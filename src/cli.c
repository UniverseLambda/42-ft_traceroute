/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:30:50 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 16:35:07 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cli.h"

#include <stdio.h>
#include <stdlib.h>

#include "inc/ft_stdutil.h"

struct	s_cli_builder
{
	char	*host;
	size_t	index;
};

__attribute__ ((__noreturn__))
static void	usage(void)
{
	fprintf(stderr, "Usage:\n  traceroute host\nOptions:\n");
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
	if (arg[0] == '-')
	{
		if (ft_strcmp(arg, "--help") == 0)
			usage();
		else
			bad_option(builder->index, arg);
	}
	if (builder->host != NULL)
		extra_arg(builder->index, arg);
	builder->host = arg;
	builder->index += 1;
}

char	*cli(t_slice args)
{
	struct s_cli_builder	builder;

	ft_memset(&builder, 0, sizeof(builder));
	slice_charptr_buildfrom(&args, (void *)build_from, &builder);
	if (builder.host == NULL)
		usage();
	return (builder.host);
}
