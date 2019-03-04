/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:31:49 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/28 18:35:10 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

int		nm(char *ptr, char *name, int aff)
{
	unsigned int	magic;

	magic = *((unsigned int*)ptr);
	if ((magic == MH_MAGIC_64 || magic == MH_MAGIC) && aff == 1)
		ft_printf("\n%s:\n", name);
	if (aff == 2 && magic == MH_MAGIC)
		ft_printf("%s:\n", name);
	if (magic == MH_MAGIC_64)
		return (handle_64(ptr));
	else if (magic == MH_MAGIC)
		return (handle_32(ptr));
	else if (magic == FAT_CIGAM)
		return (handle_fat(ptr, name));
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		return (handle_ar(ptr, name));
	ft_fd_printf(2,
		"ft_nm: file %s was not recognized as a valid object file\n", name);
	return (0);
}
