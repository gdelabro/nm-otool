/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:31:49 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/06 17:21:50 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

int		nm(char *ptr, char *name, int aff)
{
	unsigned int	magic;

	magic = *((unsigned int*)ptr);
	if ((magic == MH_MAGIC_64 || magic == MH_MAGIC_64
				|| magic == FAT_CIGAM) && aff)
		ft_printf("\n%s:\n", name);
	if (magic == MH_MAGIC_64)
		return (handle_64(ptr));
	else if (magic == MH_MAGIC)
		return (handle_32(ptr));
	else if (magic == FAT_CIGAM)
		return (handle_fat(ptr, name));
	else if (!ft_strncmp(ptr, ARMAG, SARMAG))
		return (handle_ar(ptr, name));
	ft_printf("ft_nm: file %s was not recognized as a valid object file\n",
			name);
	return (0);
}
