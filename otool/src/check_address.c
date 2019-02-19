/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:14:36 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/19 16:17:34 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void	my_address_pages(int mode, void *ptr, int size)
{
	static void		*ptr_start = NULL;
	static void		*ptr_end = NULL;

	if (!mode)
	{
		ptr_start = ptr;
		ptr_end = ptr + size;
	}
	else
	{
		if (ptr < ptr_start || ptr > ptr_end)
			ft_exit(9, NULL);
	}
}

void	init_check_address(void *ptr, int size)
{
	my_address_pages(0, ptr, size);
}

void	check_address(void *ptr)
{
	my_address_pages(1, ptr, 0);
}
