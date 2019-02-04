/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:32:46 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/04 19:39:02 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

int   handle_64(char *ptr, char *name)
{
  t_nm_64      *s;

  !(s = malloc(sizeof(t_nm_64))) ? ft_exit(1, "") : 0;
  s->header = (struct mach_header_64 *)ptr;
  s->lc = (void*)ptr + sizeof(struct mach_header_64);
  s->ncmds = s->header->ncmds;
  s->i = -1;
  while (++(s->i) < s->ncmds)
  {
    if (s->lc->cmd == LC_SEGMENT_64)
      handle_sections_64(s, ptr, name);
    s->lc = (void*)(s->lc) + s->lc->cmdsize;
  }
  free_structs(s);
  return (1);
}
