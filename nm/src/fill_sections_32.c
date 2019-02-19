/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sections_32.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:43:25 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/19 15:39:12 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

t_sections	*creat_new_section_32(char sectname[16], int seg_num)
{
	t_sections		*new_sec;

	new_sec = malloc(sizeof(*new_sec));
	if (!new_sec)
		ft_exit(1, "");
	ft_bzero(new_sec->sectname, 16);
	ft_strcpy(new_sec->sectname, sectname);
	new_sec->seg_num = seg_num;
	new_sec->next = NULL;
	return (new_sec);
}

t_sections	*add_section_32(t_nm_32 *s, struct section *sec)
{
	t_sections	*new_sec;
	int			i;

	i = s->sec ? s->sec->seg_num + 1 : 1;
	new_sec = creat_new_section_32(sec->sectname, i);
	new_sec->next = s->sec;
	s->sec = new_sec;
	return (s->sec);
}

void		fill_sections_32(t_nm_32 *s)
{
	struct segment_command	*seg;
	struct section			*sec;
	uint32_t				i;

	i = -1;
	seg = (struct segment_command*)(s->lc);
	sec = (void*)(seg + 1);
	check_address(seg);
	check_address(sec);
	while (++i < seg->nsects)
	{
		check_address(sec);
		s->sec = add_section_32(s, sec);
		sec += 1;
	}
}
