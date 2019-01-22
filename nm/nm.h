/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:53:45 by gdelabro          #+#    #+#             */
/*   Updated: 2019/01/22 18:00:07 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

#include "../libft/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <mach/machine.h>
# include <stdbool.h>

typedef struct s_nlist
{
    union
    {
        uint32_t  n_strx;
    } n_un;
    uint8_t n_type;
    uint8_t n_sect;
    uint16_t n_desc;
    uint64_t n_value;
    char    *n_name;
    struct s_nlist  *next;
}       t_nlist;

typedef struct s_sections
{
  char            sectname[16];
  int             seg_num;
  void            *next;
}              t_sections;

typedef struct s_nm_64
{
  int                     ncmds;
  struct mach_header_64  *header;
  struct load_command    *lc;
  struct symtab_command  *sym;
  t_nlist                *symbols;
  t_sections             *sec;
  int                     i;
}              t_nm_64;


typedef struct s_nm_32
{
  int                     ncmds;
  struct mach_header     *header;
  struct load_command    *lc;
  struct symtab_command  *sym;
  t_nlist                *symbols;
  t_sections             *sec;
  int                     i;
}                t_nm_32;

typedef struct s_nm_fat
{
  int                     ncmds;
  struct fat_header      *header;
  struct fat_arch        *fat_arch;
  struct load_command    *lc;
  struct symtab_command  *sym;
  t_nlist                *symbols;
  t_sections             *sec;
  int                     i;
}                t_nm_fat;

void    ft_exit(int err, char *msg);
void    fill_sections_64(t_nm_64 *s);
void    fill_sections_32(t_nm_32 *s);
void    fill_sections_fat(t_nm_fat *s);
void    print_symbols(t_nlist *sym, t_sections *sec);
int     handle_64(char *ptr);
int     handle_32(char *ptr);
int     handle_fat(char *ptr);
int     nm(char *ptr);

#endif
