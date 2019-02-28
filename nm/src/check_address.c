/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:14:36 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/28 16:12:40 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

int		my_address_pages(int mode, void *ptr, int size)
{
	static void		*ptr_start = NULL;
	static void		*ptr_end = NULL;

	if (!mode)
	{
		ptr_start = ptr;
		ptr_end = ptr + size;
	}
	else if (mode == 1)
		if (ptr < ptr_start || ptr > ptr_end)
			ft_exit(7, NULL);
	if (ptr < ptr_start || ptr >= ptr_end)
		return (0);
	return (1);
}

void	init_check_address(void *ptr, int size)
{
	my_address_pages(0, ptr, size);
}

void	check_address(void *ptr)
{
	my_address_pages(1, ptr, 0);
}

int		is_in_address(void *ptr)
{
	return (my_address_pages(2, ptr, 0));
}
