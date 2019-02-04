/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:21:17 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/04 20:12:39 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void  ft_abort_file(int err, char *msg)
{
  if (err == 2)
    ft_printf("%s: open failed or file does not exist\n", msg);
  else if (err == 3)
    ft_printf("exit: mmap failed\n");
  else if (err == 4)
    ft_printf("%s: fstat failed\n", msg);
  else if (err == 5)
    ft_printf("exit: munmap failed\n");
  else if (err == 6)
    ft_printf("exit: close failed\n");
  else
    ft_printf("exit: error unkonwn\n");
}

void  ft_exit(int err, char *msg)
{
  if (err == 1)
    ft_printf("exit: malloc failed: exiting\n");
  else if (err == 2)
    ft_printf("%s: exit: open failed or file does not exist\n", msg);
  else if (err == 3)
    ft_printf("%s: mmap failed: exiting\n", msg);
  else if (err == 4)
    ft_printf("%s: fstat failed: exiting\n", msg);
  else if (err == 5)
    ft_printf("%s: munmap failed: exiting\n", msg);
  else if (err == 6)
    ft_printf("%s: close failed: exiting\n", msg);
  else
    ft_printf("%s: error unkonwn: exiting\n", msg);
  exit(EXIT_FAILURE);
}

void  otool_one_file(char *name)
{
  int   fd;
  char  *ptr;
  int   ret;
  struct stat buf;

  if ((fd = open(name, O_RDONLY)) < 0)
    return (ft_abort_file(2, name));
  if (fstat(fd, &buf) < 0 && close(fd) > 0)
    ft_abort_file(4, name);
  if ((ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
    ft_exit(3, name);
  ret = otool(ptr, name);
  if ((munmap(ptr, buf.st_size)))
    ft_exit(5, name);
  if (close(fd) < 0)
    ft_exit(6, name);
}

int   main(int ac, char **av)
{
  int i;

  i = 0;
  if (ac == 1)
    ft_printf("usage: ./ft_otool <object file> ...\n");
  while (++i < ac)
    otool_one_file(av[i]);
}
