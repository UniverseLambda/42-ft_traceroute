/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:30:51 by clsaad            #+#    #+#             */
/*   Updated: 2023/07/31 15:43:16 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "inc/cli.h"

int main(int argc, char **argv)
{
	char	*target;

	target = cli(slice_new(argv + 1, argc - 1));
	printf("Target: %s\n", target);
	return (0);
}
