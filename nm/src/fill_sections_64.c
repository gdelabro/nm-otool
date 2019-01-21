/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_sections_64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:43:25 by gdelabro          #+#    #+#             */
/*   Updated: 2019/01/21 20:51:24 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

t_sections *creat_new_section(char sectname[16], int seg_num)
{
  t_sections  *new_sec;

  new_sec = malloc(sizeof(*new_sec));
  if (!new_sec)
    ft_exit(1, "");
  ft_bzero(new_sec->sectname, 16);
  ft_strcpy(new_sec->sectname, sectname);
  new_sec->seg_num = seg_num;
  new_sec->next = NULL;
  return (new_sec);
}

t_sections  *add_section(t_nm_64 *s, struct section_64 *sec, struct segment_command_64 *seg)
{
  t_sections *new_sec;
  int         i;

  i = s->sec ? s->sec->seg_num + 1 : 1;
  new_sec = creat_new_section(sec->sectname, i);
  new_sec->next = s->sec;
  s->sec = new_sec;
  return (s->sec);
}

void   fill_sections_64(t_nm_64 *s)
{
  struct segment_command_64 *seg;
	struct section_64			*sec;
  int                   i;

  i = -1;
  seg = (struct segment_command_64*)(s->lc);
  sec = (void*)(seg + 1);
  while (++i < seg->nsects)
  {
    s->sec = add_section(s, sec, seg);
    sec += 1;
  }
}
