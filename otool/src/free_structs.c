/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:36:03 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/04 17:40:02 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void free_arch(t_arch *arch)
{
  if (!arch)
    return ;
  if (arch->next)
    free_arch(arch->next);
  free(arch);
}

void    free_structs(void *s)
{
  s ? free(s) : 0;
}
