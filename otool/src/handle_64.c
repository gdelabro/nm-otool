/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:32:46 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/08 19:05:15 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void	aff_header_64(struct mach_header_64 *header)
{
	ft_printf("Mach header\n");
	ft_printf("      magic cputype cpusubtype  caps");
	ft_printf("    filetype ncmds sizeofcmds      flags\n");
	ft_printf(" %#.8x %7d %10d %5#.2x %11d %5d %10d %#.8x\n",
	header->magic, header->cputype,
	CPU_SUBTYPE_INTEL_FAMILY(header->cpusubtype),
	(unsigned int)(header->cpusubtype) >> 24, header->filetype, header->ncmds,
	header->sizeofcmds, header->flags);
}

int		handle_64(char *ptr, char *name, t_option *o)
{
	t_nm_64			*s;

	!(s = malloc(sizeof(t_nm_64))) ? ft_exit(1, "") : 0;
	s->header = (struct mach_header_64 *)ptr;
	s->lc = (void*)ptr + sizeof(struct mach_header_64);
	s->ncmds = s->header->ncmds;
	s->i = -1;
	if (o->d || o->t)
		ft_printf("%s:\n", name);
	while (++(s->i) < s->ncmds)
	{
		if (s->lc->cmd == LC_SEGMENT_64)
			handle_sections_64(s, ptr, o);
		s->lc = (void*)(s->lc) + s->lc->cmdsize;
	}
	o->h ? aff_header_64(s->header) : 0;
	free_structs(s);
	return (1);
}
