/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:31:49 by gdelabro          #+#    #+#             */
/*   Updated: 2019/01/22 17:59:11 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

int  nm(char *ptr)
{
  int magic;

  magic = *(int*)ptr;
  if (magic == MH_MAGIC_64)
    return (handle_64(ptr));
  else if (magic == MH_MAGIC)
    return (handle_32(ptr));
  else if (magic == FAT_MAGIC)
    return (handle_fat(ptr));
  else
    ft_printf("%x", magic,"ft_nm: The file was not recognized as a valid object file\n");
  return (0);
}
