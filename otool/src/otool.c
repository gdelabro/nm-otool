/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:31:49 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/19 16:14:47 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

int		otool(char *ptr, char *name, t_option *o)
{
	unsigned int	magic;

	check_address(ptr);
	magic = *((unsigned int*)ptr);
	if (magic == MH_MAGIC_64)
		return (handle_64(ptr, name, o));
	else if (magic == MH_MAGIC)
		return (handle_32(ptr, name, o));
	else if (magic == FAT_CIGAM)
		return (handle_fat(ptr, name, o));
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		return (handle_ar(ptr, name, o));
	ft_printf("ft_otool: file %s was not recognized as a valid object file\n",
			name);
	return (0);
}
