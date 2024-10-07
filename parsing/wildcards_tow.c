/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_tow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:05:06 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 12:05:08 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	last_wildcards(char *str, int x)
{
	t_quote	q;
	int		l;
	int		i;

	x++;
	i = x - 1;
	q.in_double_quote = 0;
	q.in_single_quote = 0;
	while (str[x])
	{
		l = chacke_q(str[x], &q);
		if (!l && str[x] == '*')
			return (0);
		x++;
	}
	if (str[i] && !str[i + 1])
		return (1);
	return (2);
}

int	ft_strlen_doubl(char **str)
{
	int	x;

	x = 0;
	if (!str)
		return (0);
	while (str[x])
	{
		x++;
	}
	return (x);
}

void	swapp(int ac, char **av)
{
	char	*c;
	int		x;
	int		xx;

	x = 0;
	while (x < ac)
	{
		xx = x + 1;
		while (av[xx])
		{
			if (ft_strcmp(av[x], av[xx]) > 0)
			{
				c = av[x];
				av[x] = av[xx];
				av[xx] = c;
			}
			xx++;
		}
		x++;
	}
}
