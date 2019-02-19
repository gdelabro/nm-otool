/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 17:41:48 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/19 16:51:12 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void	print_arch(t_arch *arch, char *ptr)
{
	t_arch			*a;
	struct ar_hdr	*header;

	a = arch;
	while (a)
	{
		header = (struct ar_hdr*)(ptr + a->off);
		print_archive_header(header);
		a = a->next;
	}
}

void	print_archive_header(struct ar_hdr *h)
{
	ft_printf("%.7d %d/%-3d% 6d% 11d ",
	ft_atoi(h->ar_mode), ft_atoi(h->ar_uid), ft_atoi(h->ar_gid),
	ft_atoi(h->ar_size), ft_atoi(h->ar_date));
	write(1, h->ar_name, ft_strchr(h->ar_name, ' ') - h->ar_name);
	ft_putendl("");
}

void	print_section_data(char *ptr, uint32_t size, void *addr)
{
	int		i;

	i = -1;
	ft_printf("Contents of (__DATA,__data) section\n");
	while (++i < (int)size)
	{
		!(i % 16) ? ft_printf("%016llx\t", addr + i) : 0;
		ft_printf("%02x", *(unsigned char*)(ptr + i));
		ft_printf(" ");
		(i % 16) == 15 || i + 1 == (int)size ? ft_printf("\n") : 0;
	}
}

void	print_sections(char *ptr, uint32_t size, void *addr)
{
	int		i;

	i = -1;
	ft_printf("Contents of (__TEXT,__text) section\n");
	while (++i < (int)size)
	{
		!(i % 16) ? ft_printf("%016llx\t", addr + i) : 0;
		ft_printf("%02x", *(unsigned char*)(ptr + i));
		ft_printf(" ");
		(i % 16) == 15 || i + 1 == (int)size ? ft_printf("\n") : 0;
	}
}
