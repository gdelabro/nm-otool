/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:32:46 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/08 19:04:40 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

int		power_2(int pow)
{
	int		res;

	res = 2;
	while (--pow > 0)
		res *= 2;
	return (res);
}

void	aff_fat_header(struct fat_header *header)
{
	ft_printf("Fat headers\nfat_magic %#.8x\nnfat_arch %d\n",
			swap_uint32(header->magic), swap_uint32(header->nfat_arch));
}

void	aff_fat_arch(struct fat_arch *arch, int i)
{
	ft_printf("architecture %d\n", i);
	ft_printf("    cputype %d\n", swap_uint32(arch->cputype));
	ft_printf("    cpusubtype %d\n",
			CPU_SUBTYPE_INTEL_FAMILY(swap_uint32(arch->cpusubtype)));
	ft_printf("    capabilities %#p\n",
			(unsigned int)(swap_uint32(arch->cpusubtype)) >> 24);
	ft_printf("    offset %d\n", swap_uint32(arch->offset));
	ft_printf("    size %d\n", swap_uint32(arch->size));
	ft_printf("    align 2^%d (%d)\n", swap_uint32(arch->align),
			power_2(swap_uint32(arch->align)));
}

int		handle_fat(char *ptr, char *name, t_option *o)
{
	t_nm_fat			*s;
	struct mach_header	*ptr2;

	!(s = malloc(sizeof(t_nm_fat))) ? ft_exit(1, "") : 0;
	s->header = (struct fat_header *)ptr;
	s->i = -1;
	s->fat_arch = (struct fat_arch*)(s->header + 1);
	s->ptr = NULL;
	o->f ? aff_fat_header(s->header) : 0;
	while (++s->i < swap_uint32(s->header->nfat_arch))
	{
		ptr2 = (void*)ptr + swap_uint32(s->fat_arch->offset);
		if (ptr2->magic == MH_MAGIC_64 ||
				(s->i + 1 == swap_uint32(s->header->nfat_arch) && !s->ptr))
			s->ptr = ptr2;
		if (o->f)
			aff_fat_arch(s->fat_arch, s->i);
		s->fat_arch += 1;
	}
	otool(s->ptr, name, o);
	free(s);
	return (1);
}
