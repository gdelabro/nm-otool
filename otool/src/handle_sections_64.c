/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sections_64.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:43:25 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/07 18:23:37 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void	handle_sections_64(t_nm_64 *s, char *ptr, t_option *o)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	int							i;

	i = -1;
	seg = (struct segment_command_64*)(s->lc);
	sec = (void*)(seg + 1);
	while (++i < (int)seg->nsects)
	{
		if (!ft_strcmp(sec->segname, SEG_TEXT) &&
				!ft_strcmp(sec->sectname, SECT_TEXT) && o->t)
			print_sections(ptr + sec->offset, sec->size, (void*)sec->addr);
		if (!ft_strcmp(sec->segname, SEG_DATA) &&
				!ft_strcmp(sec->sectname, SECT_DATA) && o->d)
			print_section_data(ptr + sec->offset, sec->size, (void*)sec->addr);
		sec += 1;
	}
}
