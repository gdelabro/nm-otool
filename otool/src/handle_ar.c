/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:32:46 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/08 16:37:00 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void		print_ar(char *ptr, t_nm_ar *s, char *name, t_option *o)
{
	char		*name2;
	t_arch		*arch;

	arch = s->arch;
	o->a ? print_arch(s->arch, ptr) : 0;
	while (arch)
	{
		name2 = malloc(sizeof(char) * (ft_strlen(name) +
					ft_strlen(arch->name) + 3));
		name2[0] = 0;
		ft_strcpy(name2, name);
		ft_strcpy(name2 + ft_strlen(name2), "(");
		ft_strcpy(name2 + ft_strlen(name2), arch->name);
		ft_strcpy(name2 + ft_strlen(name2), ")");
		s->header = (struct ar_hdr*)(ptr + arch->off);
		otool((char*)((char*)(s->header + 1) +
					ft_atoi(ft_strchr(s->header->ar_name, '/') + 1)), name2, o);
		free(name2);
		arch = arch->next;
	}
}

t_arch		*creat_file_member_arch(char *ptr, t_nm_ar *s, int i, t_option *o)
{
	t_arch	*new_arch;

	(void)o;
	!(new_arch = malloc(sizeof(t_arch))) ? ft_exit(1, "") : 0;
	s->header = (struct ar_hdr*)(ptr + s->ran[i].ran_off);
	new_arch->off = s->ran[i].ran_off;
	new_arch->strx = s->ran[i].ran_un.ran_strx;
	new_arch->name = (char*)(s->header + 1);
	new_arch->next = NULL;
	return (new_arch);
}

void		delete_doublon(t_arch *arch)
{
	void	*tmp;

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

t_arch		*add_file_member_arch(char *ptr, t_nm_ar *s, int i, t_option *o)
{
	t_arch	*new_arch;
	t_arch	*arch;

	arch = s->arch;
	new_arch = creat_file_member_arch(ptr, s, i, o);
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

int			handle_ar(char *ptr, char *name, t_option *o)
{
	t_nm_ar				*s;
	int					size;
	int					i;

	!(s = malloc(sizeof(t_nm_ar))) ? ft_exit(1, "") : 0;
	ft_printf("Archive : %s\n", name);
	s->header = (struct ar_hdr *)(ptr + SARMAG);
	o->a ? print_archive_header(s->header) : 0;
	size = *(int*)((void*)(s->header + 1) +
			ft_atoi(ft_strchr(s->header->ar_name, '/') + 1));
	size /= sizeof(s->ran);
	s->ran = (struct ranlib*)((void*)(s->header + 1) +
			ft_atoi(ft_strchr(s->header->ar_name, '/') + 1) + 4);
	s->arch = NULL;
	i = -1;
	while (++i < size)
		s->arch = add_file_member_arch(ptr, s, i, o);
	delete_doublon(s->arch);
	print_ar(ptr, s, name, o);
	free_arch(s->arch);
	free(s);
	return (1);
}
