/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:32:46 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/22 17:42:37 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

void		print_ar(char *ptr, t_nm_ar *s, char *name)
{
	t_arch	*arch;

	arch = s->arch;
	while (arch)
	{
		s->header = (struct ar_hdr*)(ptr + arch->off);
		ft_printf("\n%s(%s):\n", name, arch->name);
		nm((char*)((char*)(s->header + 1)
				+ ft_atoi(ft_strchr(s->header->ar_name, '/') + 1)), name, 0);
		arch = arch->next;
	}
}

t_arch		*creat_file_member_arch(char *ptr, t_nm_ar *s, int i)
{
	t_arch	*new_arch;

	!(new_arch = malloc(sizeof(t_arch))) ? ft_exit(1, "") : 0;
	s->header = (struct ar_hdr*)(ptr + s->ran[i].ran_off);
	new_arch->off = s->ran[i].ran_off;
	check_address(ptr + new_arch->off);
	new_arch->strx = s->ran[i].ran_un.ran_strx;
	new_arch->name = (char*)(s->header + 1);
	new_arch->next = NULL;
	return (new_arch);
}

void		delete_doublon(t_arch *arch)
{
	void		*tmp;

	while (arch && arch->next)
	{
		if (arch->off == arch->next->off)
		{
			tmp = arch->next->next;
			free(arch->next);
			arch->next = tmp;
			return (delete_doublon(arch));
		}
		arch = arch->next;
	}
}

t_arch		*add_file_member_arch(char *ptr, t_nm_ar *s, int i)
{
	t_arch		*new_arch;
	t_arch		*arch;

	arch = s->arch;
	new_arch = creat_file_member_arch(ptr, s, i);
	if (!arch || (new_arch->off < arch->off
				&& (new_arch->next = arch) != (void*)-1))
		return (new_arch);
	while (arch)
	{
		if (!arch->next && (arch->next = new_arch))
			return (s->arch);
		else if (arch->next->off > new_arch->off)
		{
			new_arch->next = arch->next;
			arch->next = new_arch;
			return (s->arch);
		}
		arch = arch->next;
	}
	return (s->arch);
}

int			handle_ar(char *ptr, char *name)
{
	t_nm_ar				*s;
	int					size;
	int					i;

	!(s = malloc(sizeof(t_nm_ar))) ? ft_exit(1, "") : 0;
	s->header = (struct ar_hdr *)(ptr + SARMAG);
	check_address(s->header);
	check_address(s->header + 1);
	size = *(int*)((void*)(s->header + 1)
			+ ft_atoi(ft_strchr(s->header->ar_name, '/') + 1));
	size /= sizeof(s->ran);
	s->ran = (struct ranlib*)((void*)(s->header + 1)
			+ ft_atoi(ft_strchr(s->header->ar_name, '/') + 1) + 4);
	s->arch = NULL;
	i = -1;
	while (++i < size)
		s->arch = add_file_member_arch(ptr, s, i);
	delete_doublon(s->arch);
	print_ar(ptr, s, name);
	free_arch(s->arch);
	free(s);
	return (1);
}
