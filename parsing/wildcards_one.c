/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:52:21 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 12:05:02 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*chech_be(char *str, int x)
{
	int		i;
	int		j;
	t_quote	q;
	int		l;
	char	*re;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	x--;
	i = 0;
	j = 0;
	while (x >= 0)
	{
		l = chacke_q(str[x], &q);
		if (str[x] == '*' && !l)
			break ;
		j++;
		x--;
	}
	re = malloc(j + 1);
	while (i < j)
		re[i++] = str[++x];
	re[i] = '\0';
	return (re);
}

char	*check_aft(char *str, int x, int xx)
{
	int		i;
	int		j;
	char	*re;

	i = 0;
	j = 0;
	while (str[x])
	{
		x++;
		j++;
	}
	re = malloc(j + 1);
	while (i < j)
	{
		re[i++] = str[xx++];
	}
	re[i] = '\0';
	return (re);
}

int	ch_f(char *str, char *name, int *i)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] != name[*i])
			return (1);
		x++;
		(*i)++;
	}
	return (0);
}

int	ch_m(char *str, char *name, int *i)
{
	int	x;

	x = 0;
	while (name[*i])
	{
		x = 0;
		while (str[x] && name[*i] && name[*i] == str[x])
		{
			x++;
			(*i)++;
		}
		if (!str[x])
			return (0);
		(*i)++;
	}
	return (1);
}

int	ch_l(char *str, char *name)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	x = ft_strlen(str);
	i = ft_strlen(name);
	while (x > 0)
	{
		if (name[i - 1] != str[x - 1])
			return (1);
		i--;
		x--;
	}
	return (0);
}
