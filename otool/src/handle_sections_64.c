/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sections_64.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:43:25 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/04 20:30:48 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void   handle_sections_64(t_nm_64 *s, char *ptr, char *name)
{
  struct segment_command_64 *seg;
	struct section_64			*sec;
  int                   i;

  i = -1;
  seg = (struct segment_command_64*)(s->lc);
  sec = (void*)(seg + 1);
  while (++i < (int)seg->nsects)
  {
    if(!ft_strcmp(sec->segname, SEG_TEXT) &&
      !ft_strcmp(sec->sectname, SECT_TEXT))
      print_sections(ptr + sec->offset, sec->size, name, (void*)sec->addr);
    sec += 1;
  }
}
