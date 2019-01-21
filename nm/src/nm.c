/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:31:49 by gdelabro          #+#    #+#             */
/*   Updated: 2019/01/18 15:41:44 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

int  nm(char *ptr)
{
  int magic;

  magic = *(int*)ptr;
  if (magic == MH_MAGIC_64)
    return (handle_64(ptr));
  //else if (magic == MH_MAGIC)
  //  ft_printf("file is a binary 32-bit.\n");
  return (0);
}
