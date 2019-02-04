/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 17:41:48 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/04 20:30:31 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void print_number_hexa(unsigned char c)
{
  ft_printf("%01x", c / 16);
  ft_printf("%01x", c % 16);
}

void print_sections(char *ptr, uint32_t size, char *name, void *addr)
{
  int   i;

  i = -1;
  ft_printf("%s:\nContents of (__TEXT,__text) section\n", name);
  while (++i < (int)size)
  {
    !(i % 16) ? ft_printf("%016llx\t", addr + i) : 0;
    print_number_hexa(*(char*)(ptr + i));
    ft_printf(" ");
    (i % 16) == 15 || i + 1 == (int)size ? ft_printf("\n") : 0;
  }
}
