/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 17:41:48 by gdelabro          #+#    #+#             */
/*   Updated: 2019/01/25 18:28:35 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

char define_section_type(t_nlist *sym, t_sections *sec)
{
  while (sec)
  {
    if (sym->n_sect == sec->seg_num)
    {
      if (!ft_strcmp(sec->sectname, SECT_DATA))
        return ('D');
      if (!ft_strcmp(sec->sectname, SECT_TEXT))
        return ('T');
      if (!ft_strcmp(sec->sectname, SECT_BSS))
        return ('B');
      return ('S');
    }
    sec = sec->next;
  }
  return ('d');
}

char  define_type(t_nlist *sym, t_sections *sec)
{
  char ret;

  ret = '?';
  if ((sym->n_type & N_TYPE) == N_UNDF)
		ret = sym->n_value ? 'C' : 'U';
  else if ((sym->n_type & N_TYPE) == N_PBUD)
  	ret = 'U';
  else if ((sym->n_type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((sym->n_type & N_TYPE) == N_INDR)
		ret = 'I';
  else if ((sym->n_type & N_TYPE) == N_SECT)
    ret = define_section_type(sym, sec);
  if ((sym->n_type & N_STAB) != 0)
    ret = 'Z';
  if ((sym->n_type & N_EXT) == 0 && ret != '?')
    ret += 32;
  return (ret);
}

void print_symbols(t_nlist *sym, t_sections *sec)
{
  t_nlist *tmp;

  tmp = sym;
  while (tmp)
  {
    tmp->n_sect ? ft_printf("%.16llx %c %s\n", tmp->n_value,
    define_type(tmp, sec), tmp->n_name) :
    ft_printf("% 16s %c %s\n", "",
    define_type(tmp, sec), tmp->n_name);
    tmp = tmp->next;
  }
}
