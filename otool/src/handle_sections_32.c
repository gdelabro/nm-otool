/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sections_32.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:43:25 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/25 16:09:36 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void	handle_sections_32(t_nm_32 *s, char *ptr, t_option *o)
{
	struct segment_command	*seg;
	struct section			*sec;
	int						i;

	i = -1;
	seg = (struct segment_command*)(s->lc);
	check_address(seg);
	sec = (void*)(seg + 1);
	while (++i < (int)seg->nsects)
	{
		check_address(sec);
		check_address(sec + 1);
		if (!ft_strcmp(sec->segname, SEG_TEXT) &&
				!ft_strcmp(sec->sectname, SECT_TEXT) && o->t)
			print_sections(ptr + sec->offset, sec->size,
					(void*)(uint64_t)sec->addr, 0);
		if (!ft_strcmp(sec->segname, SEG_DATA) &&
				!ft_strcmp(sec->sectname, SECT_DATA) && o->d)
			print_section_data(ptr + sec->offset, sec->size,
					(void*)(uint64_t)sec->addr, 0);
		sec += 1;
	}
}
