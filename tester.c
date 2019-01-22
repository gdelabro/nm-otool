/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:46:29 by gdelabro          #+#    #+#             */
/*   Updated: 2019/01/22 17:56:33 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"

void write_in(char *dest, char *src)
{
  int i;

  while (*dest)
    dest++;
  i = -1;
  while (src[++i])
  {
    *dest = src[i];
    dest++;
  }
  *dest = 0;
}

int main(int argc, char **argv)
{
  char *command;

  command = malloc(100);

  command[0] = 0;
  write_in(command, "rm tmp1 tmp2 ");
  system(command);

  command[0] = 0;
  write_in(command, "./ft_nm ");
  write_in(command, argv[1]);
  write_in(command, " > tmp1");
  system(command);

  command[0] = 0;
  write_in(command, "nm ");
  write_in(command, argv[1]);
  write_in(command, " > tmp2");
  system(command);

  command[0] = 0;
  write_in(command, "diff tmp1 tmp2");
  system(command);
}
