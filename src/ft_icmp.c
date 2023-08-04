/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_icmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clsaad <clsaad@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:04:26 by clsaad            #+#    #+#             */
/*   Updated: 2023/08/04 13:43:21 by clsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_icmp.h"

#include <netinet/ip_icmp.h>
#include <netinet/ip.h>

#include "inc/ft_stdutil.h"
#include "inc/numutil.h"

typedef struct icmphdr	t_icmphdr;

static size_t	get_ipdata_offset(const void *ipv4_header)
{
	return (((const struct iphdr *)ipv4_header)->ihl * 4);
}

static bool	is_buffer_sufficient(const char *buffer, size_t size, const char *iphdr)
{
	if ((ssize_t)size < iphdr - buffer)
		return (false);
	return ((ssize_t)size >= (iphdr + get_ipdata_offset(iphdr) + 8) - buffer);
}

static size_t	get_icmp_packet_type(const t_icmphdr *icmphdr)
{
	if (icmphdr->type == 3 && icmphdr->code == 3)
		return (ICMP_PORT_UNREACHABLE);
	if (icmphdr->type == 11 && icmphdr->code == 0)
		return (ICMP_TTL_EXCEEDED);
	return (ICMP_INVALID_TYPE);
}

#include <stdio.h>
#include <ctype.h>
static void dump_buffer(const char *buffer, size_t buf_size)
{
	size_t i;

	for (i = 0; i < (buf_size / 16) + !!(buf_size % 16); ++i)
	{
		printf("%ld\t|\t", i * 16);

		size_t j;
		for (j = 0; j < 16; ++j)
		{
			if (j == 8)
				putchar(' ');
			if (j + (i * 16) >= buf_size)
			{
				printf("   ");
			}
			else
			{
				int v = (int)buffer[j + (i * 16)] & 0xFF;
				printf("%.2X ", v);
			}
		}

		printf("   ");
		for (j = 0; j < 16; ++j)
		{
			if (j == 8)
				putchar(' ');
			if (j + (i * 16) >= buf_size)
			{
				printf("   ");
			}
			else
			{
				char c = buffer[j + (i * 16)];
				printf("%c ", isprint(c) ? c : '.');
			}
		}

		puts("");
	}
	puts("");
}

t_icmp_res	parse_icmp_resp(const char *buffer, size_t size, int start_port, int end_port)
{
	const t_icmphdr	*icmphdr = (t_icmphdr *)(buffer + get_ipdata_offset(buffer));
	const char		*orig_iphdr = buffer + get_ipdata_offset(buffer) + 8;
	const char		*orig_data;
	t_icmp_res		result;

	ft_memset(&result, 0, sizeof(result));
	if (!is_buffer_sufficient(buffer, size, orig_iphdr))
		return (result);
	orig_data = orig_iphdr + get_ipdata_offset(orig_iphdr);
	result.icmp_packet_type = get_icmp_packet_type(icmphdr);
	if (result.icmp_packet_type == ICMP_INVALID_TYPE)
		return (result);
	if (orig_iphdr[9] != 0x11)
		return (result);
	result.dst_port = read_u16_be(orig_data + 2);
	if (start_port > result.dst_port || result.dst_port >= end_port)
	{
		dump_buffer(buffer, size);
		return (result);
	}
	result.src_port = read_u16_be(orig_data);
	ft_memcpy(&(result.emitter.s_addr), buffer + 12, 4);
	ft_memcpy(&(result.target.s_addr), orig_iphdr + 16, 4);
	result.valid = true;
	return (result);
}
