/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:21:17 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/08 18:44:55 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void	ft_abort_file(int err, char *msg)
{
	if (err == 2)
		ft_fd_printf(2, "%s: open failed or file does not exist\n", msg);
	else if (err == 3)
		ft_fd_printf(2, "exit: mmap failed\n");
	else if (err == 4)
		ft_fd_printf(2, "%s: fstat failed\n", msg);
	else if (err == 5)
		ft_fd_printf(2, "exit: munmap failed\n");
	else if (err == 6)
		ft_fd_printf(2, "exit: close failed\n");
	else if (err == 7)
		ft_fd_printf(2, "exit: %s is not a regular file\n", msg);
	else
		ft_fd_printf(2, "exit: error unkonwn\n");
}

void	ft_exit(int err, char *msg)
{
	if (err == 1)
		ft_fd_printf(2, "exit: malloc failed: exiting\n");
	else if (err == 2)
		ft_fd_printf(2, "%s: exit: open failed or file does not exist\n", msg);
	else if (err == 3)
		ft_fd_printf(2, "%s: mmap failed: exiting\n", msg);
	else if (err == 4)
		ft_fd_printf(2, "%s: fstat failed: exiting\n", msg);
	else if (err == 5)
		ft_fd_printf(2, "%s: munmap failed: exiting\n", msg);
	else if (err == 6)
		ft_fd_printf(2, "%s: close failed: exiting\n", msg);
	else if (err == 7)
		ft_fd_printf(2,
"exiting for bad option\nUsage: ./ft_otool [-fdht] -- <object files> ...\n");
	else if (err == 8)
		ft_fd_printf(2,
"exiting: no object file\nUsage: ./ft_otool [-fdht] -- <object files> ...\n");
	else
		ft_fd_printf(2, "%s: error unkonwn: exiting\n", msg);
	exit(EXIT_FAILURE);
}

void	otool_one_file(char *name, t_option *o)
{
	int				fd;
	char			*ptr;
	int				ret;
	struct stat		buf;

	if ((fd = open(name, O_RDONLY)) < 0)
		return (ft_abort_file(2, name));
	if (fstat(fd, &buf) < 0 && close(fd) != -11)
		return (ft_abort_file(4, name));
	if (S_ISDIR(buf.st_mode) && close(fd) != -11)
		return (ft_abort_file(7, name));
	if ((ptr = mmap(NULL, buf.st_size,
					PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		ft_exit(3, name);
	ret = otool(ptr, name, o);
	if ((munmap(ptr, buf.st_size)))
		ft_exit(5, name);
	if (close(fd) < 0)
		ft_exit(6, name);
}

int		main(int ac, char **av)
{
	pars_option(ac, av);
}
