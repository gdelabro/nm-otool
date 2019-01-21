/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:49:33 by gdelabro          #+#    #+#             */
/*   Updated: 2017/05/17 14:17:54 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		find_word(char *str, char *s, int i)
{
	int i2;

	i2 = 0;
	while (str[i] && s[i2])
	{
		if (str[i] != s[i2])
			return (0);
		i++;
		i2++;
	}
	if (s[i2])
		return (0);
	return (1);
}

void	fill_buf(t_pf *e, char *str, char *color)
{
	int i;

	i = -1;
	while (str[e->i] && str[e->i++] != '}')
		;
	while (color[++i])
		e->buf[e->i2++] = color[i];
}

int		test_colors(t_pf *e, char *str)
{
	if (find_word(str, "{cyan}", e->i))
		fill_buf(e, str, CYAN);
	else if (find_word(str, "{none}", e->i))
		fill_buf(e, str, NONE);
	else if (find_word(str, "{bold}", e->i))
		fill_buf(e, str, BOLD);
	else if (find_word(str, "{black}", e->i))
		fill_buf(e, str, BLACK);
	else if (find_word(str, "{red}", e->i))
		fill_buf(e, str, RED);
	else if (find_word(str, "{green}", e->i))
		fill_buf(e, str, GREEN);
	else if (find_word(str, "{brown}", e->i))
		fill_buf(e, str, BROWN);
	else if (find_word(str, "{yellow}", e->i))
		fill_buf(e, str, YELLOW);
	else if (find_word(str, "{blue}", e->i))
		fill_buf(e, str, BLUE);
	else if (find_word(str, "{magenta}", e->i))
		fill_buf(e, str, MAGENTA);
	else if (find_word(str, "{gray}", e->i))
		fill_buf(e, str, GRAY);
	else
		return (0);
	return (1);
}
