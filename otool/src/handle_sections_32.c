/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sections_32.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:43:25 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/04 20:31:02 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void   handle_sections_32(t_nm_32 *s, char *ptr, char *name)
{
  struct segment_command *seg;
	struct section			*sec;
  int                   i;

  i = -1;
  seg = (struct segment_command*)(s->lc);
  sec = (void*)(seg + 1);
  while (++i < (int)seg->nsects)
  {
    if(!ft_strcmp(sec->segname, SEG_TEXT) &&
      !ft_strcmp(sec->sectname, SECT_TEXT))
      print_sections(ptr + sec->offset, sec->size, name, (void*)(uint64_t)sec->addr);
    sec += 1;
  }
}
