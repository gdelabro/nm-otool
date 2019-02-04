/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:32:46 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/04 20:32:27 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

int   handle_fat(char *ptr, char *name)
{
  t_nm_fat           *s;
  struct mach_header *ptr2;

  !(s = malloc(sizeof(t_nm_fat))) ? ft_exit(1, "") : 0;
  s->header = (struct fat_header *)ptr;
  s->i = -1;
  s->fat_arch = (struct fat_arch*)(s->header + 1);
  while (++s->i < swap_uint32(s->header->nfat_arch))
  {
    ptr2 = (void*)ptr + swap_uint32(s->fat_arch->offset);
    if (ptr2->magic == MH_MAGIC_64)
      break ;
    s->fat_arch += 1;
  }
  if (s->i == swap_uint32(s->header->nfat_arch))
    s->fat_arch -= 1;
  otool(ptr + swap_uint32(s->fat_arch->offset), name);
  free(s);
  return (1);
}
