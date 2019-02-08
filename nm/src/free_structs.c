/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:36:03 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/06 17:13:25 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

void	free_section(t_sections *sec)
{
	if (sec->next)
		free_nlist(sec->next);
	free(sec);
}

void	free_arch(t_arch *arch)
{
	if (!arch)
		return ;
	if (arch->next)
		free_arch(arch->next);
	free(arch);
}

void	free_nlist(t_nlist *sym)
{
	if (sym->next)
		free_nlist(sym->next);
	free(sym);
}

void	free_structs(void *s, t_nlist *symbols, t_sections *sec)
{
	symbols ? free_nlist(symbols) : 0;
	sec ? free_section(sec) : 0;
	s ? free(s) : 0;
}
