/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:23:37 by gdelabro          #+#    #+#             */
/*   Updated: 2019/02/08 18:45:51 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../otool.h"

void	init_option(t_option *o)
{
	o->f = 0;
	o->d = 0;
	o->h = 0;
	o->t = 0;
	o->a = 0;
}

void	lunch_otool(int ac, char **av, t_option *o, int i)
{
	--i;
	!o->f && !o->d && !o->h && !o->a ? o->t = 1 : 0;
	if (i == ac - 1)
		ft_exit(8, NULL);
	while (++i < ac)
		otool_one_file(av[i], o);
}

int		check_option(char *str, t_option *o)
{
	int		i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == 'f')
			o->f = 1;
		else if (str[i] == 'd')
			o->d = 1;
		else if (str[i] == 'h')
			o->h = 1;
		else if (str[i] == 't')
			o->t = 1;
		else if (str[i] == 'a')
			o->a = 1;
		else
			return (-1);
	}
	return (1);
}

void	pars_option(int ac, char **av)
{
	t_option	*o;
	int			i;

	i = 0;
	!(o = malloc(sizeof(*o))) ? ft_exit(1, NULL) : 0;
	init_option(o);
	while (++i < ac)
	{
		if (av[i][0] != '-')
			break ;
		if (!ft_strcmp(av[i], "--") && ++i)
			break ;
		if (check_option(av[i], o) == -1)
		{
			free(o);
			ft_exit(7, NULL);
		}
	}
	lunch_otool(ac, av, o, i);
	free(o);
}
