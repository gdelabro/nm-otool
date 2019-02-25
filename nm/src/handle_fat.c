/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:32:46 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/25 18:25:13 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

int		handle_fat(char *ptr, char *name)
{
	t_nm_fat			*s;
	struct mach_header	*ptr2;

	!(s = malloc(sizeof(t_nm_fat))) ? ft_exit(1, "") : 0;
	s->header = (struct fat_header *)ptr;
	s->i = -1;
	s->fat_arch = (struct fat_arch*)(s->header + 1);
	s->ptr = NULL;
	while (++s->i < swap_uint32(s->header->nfat_arch))
	{
		check_address(s->fat_arch);
		check_address(s->fat_arch + 1);
		ptr2 = (void*)ptr + swap_uint32(s->fat_arch->offset);
		check_address(ptr2);
		if (ptr2->magic == MH_MAGIC_64
				|| (s->i + 1 == swap_uint32(s->header->nfat_arch) && !s->ptr))
			!s->ptr ? s->ptr = ptr2 : 0;
		s->fat_arch += 1;
	}
	if (s->i == swap_uint32(s->header->nfat_arch))
		s->fat_arch -= 1;
	check_address(ptr + swap_uint32(s->fat_arch->offset));
	nm(s->ptr, name, 0);
	free(s);
	return (1);
}
