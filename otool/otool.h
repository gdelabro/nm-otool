/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:53:45 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/08 19:07:32 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include "../libft/ft_printf.h"
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
# include <ar.h>

typedef struct				s_nm_64
{
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	int						i;
}							t_nm_64;

typedef struct				s_nm_32
{
	int						ncmds;
	struct mach_header		*header;
	struct load_command		*lc;
	int						i;
}							t_nm_32;

typedef struct				s_nm_fat
{
	int						ncmds;
	struct fat_header		*header;
	struct fat_arch			*fat_arch;
	void					*ptr;
	uint32_t				i;
}							t_nm_fat;

typedef struct				s_option
{
	int						f;
	int						d;
	int						a;
	int						h;
	int						t;
}							t_option;

typedef struct				s_arch
{
	char					*name;
	uint32_t				strx;
	uint32_t				off;
	struct s_arch			*next;
}							t_arch;

typedef struct				s_nm_ar
{
	struct ar_hdr			*header;
	struct ranlib			*ran;
	t_arch					*arch;
	int						i;
}							t_nm_ar;

void						ft_exit(int err, char *msg);
void						handle_sections_64(t_nm_64 *s,
		char *ptr, t_option *o);
void						handle_sections_32(t_nm_32 *s,
		char *ptr, t_option *o);
void						print_sections(char *ptr, uint32_t size,
		void *addr);
void						print_section_data(char *ptr, uint32_t size,
		void *addr);
void						print_archive_header(struct ar_hdr *header);
void						print_arch(t_arch *arch, char *ptr);
int							handle_64(char *ptr, char *name, t_option *o);
int							handle_32(char *ptr, char *name, t_option *o);
int							handle_fat(char *ptr, char *name, t_option *o);
int							handle_ar(char *ptr, char *name, t_option *o);
int							otool(char *ptr, char *name, t_option *o);
void						otool_one_file(char *name, t_option *o);
uint16_t					swap_uint16(uint16_t nb);
uint32_t					swap_uint32(uint32_t nb);
uint64_t					swap_uint64(uint64_t nb);
void						free_structs(void *s);
void						free_arch(t_arch *arch);
void						pars_option(int ac, char **av);

#endif
