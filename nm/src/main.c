/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:21:17 by gdelabro          #+#    #+#             */
/*   Updated: 2019/01/18 16:05:56 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../nm.h"

void  ft_exit(int err, char *msg)
{
  if (err == 1)
    ft_printf("exit: malloc failed\n");
  else
    ft_printf("exit: error unkonwn");
  exit(EXIT_FAILURE);
}

int main(int ac, char **av)
{
  int   fd;
  char  *ptr;
  int   ret;
  struct stat buf;

  if ((fd = open(av[1], O_RDONLY)) < 0)
    return (EXIT_FAILURE);
  if (fstat(fd, &buf) < 0)
    return(EXIT_FAILURE);
  if ((ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    return (EXIT_FAILURE);
  ret = nm(ptr);
  if ((munmap(ptr, buf.st_size)))
    return (EXIT_FAILURE);
  return 1;
}
