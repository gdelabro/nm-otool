/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:32:46 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/19 19:54:27 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

t_nlist		*creat_new_sym_32(struct nlist el, char *str)
{
	t_nlist		*new_sym;

	new_sym = malloc(sizeof(*new_sym));
	if (!new_sym)
		ft_exit(1, NULL);
	new_sym->n_un.n_strx = el.n_un.n_strx;
	new_sym->n_type = el.n_type;
	new_sym->n_sect = el.n_sect;
	new_sym->n_value = el.n_value;
	new_sym->n_name = str;
	new_sym->next = NULL;
	return (new_sym);
}

t_nlist		*add_symbols_32(t_nlist *sym, struct nlist el, char *str)
{
	t_nlist		*new_sym;
	t_nlist		*curr_sym;

	new_sym = creat_new_sym_32(el, str);
	curr_sym = sym;
	if (!sym || (ft_strcmp(str, sym->n_name) < 0
				&& (new_sym->next = sym) != (void*)-1))
		return (new_sym);
	while (curr_sym)
	{
		if (!curr_sym->next)
		{
			curr_sym->next = new_sym;
			return (sym);
		}
		if (ft_strcmp(str, curr_sym->next->n_name) < 0)
		{
			new_sym->next = curr_sym->next;
			curr_sym->next = new_sym;
			return (sym);
		}
		curr_sym = curr_sym->next;
	}
	return (sym);
}

t_nlist		*sort_symbols_32(int nsyms, int symoff, int stroff, char *ptr)
{
	int					i;
	char				*str_table;
	struct nlist		*el;
	t_nlist				*symbols;

	symbols = NULL;
	el = (void*)ptr + symoff;
	str_table = ptr + stroff;
	i = -1;
	while (++i < nsyms)
	{
		if (!(el[i].n_type & N_STAB))
			symbols = add_symbols_32(symbols, el[i],
					str_table + el[i].n_un.n_strx);
	}
	return (symbols);
}

void		handle_32_part_2(t_nm_32 *s, char *ptr)
{
	s->symbols = sort_symbols_32(s->sym->nsyms,
			s->sym->symoff, s->sym->stroff, ptr);
	print_symbols(s->symbols, s->sec);
	free_structs(s, s->symbols, s->sec);
}

int			handle_32(char *ptr)
{
	t_nm_32		*s;

	!(s = malloc(sizeof(t_nm_32))) ? ft_exit(1, "") : 0;
	s->header = (struct mach_header *)ptr;
	s->lc = (void*)ptr + sizeof(struct mach_header);
	check_address(s->header);
	s->ncmds = s->header->ncmds;
	s->sym = NULL;
	s->sec = NULL;
	s->i = -1;
	while (++(s->i) < s->ncmds)
	{
		check_address(s->lc);
		if (s->lc->cmd == LC_SYMTAB)
			s->sym = (struct symtab_command*)(s->lc);
		if (s->lc->cmd == LC_SEGMENT)
			fill_sections_32(s);
		s->lc = (void*)(s->lc) + s->lc->cmdsize;
	}
	!s->sym || !s->sec ? check_address(NULL) : 0;
	handle_32_part_2(s, ptr);
	return (1);
}
