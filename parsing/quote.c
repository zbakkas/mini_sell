/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:22:36 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 11:59:48 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	whithout_q_count(char *str, int x)
{
	int		c;
	int		l;
	t_quote	q;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	c = 0;
	while (str[x])
	{
		l = chacke_q(str[x], &q);
		if ((str[x] == '"' || str[x] == '\''))
		{
			if ((l == 1 && str[x] == '"') || (l == 2 && str[x] == '\''))
				c++;
		}
		else
			c++;
		x++;
	}
	return (c);
}

char	*whithout_q(char *str, int is_wildcardss)
{
	char	*re;
	int		x;
	int		c;
	int		l;
	t_quote	q;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	x = 0;
	c = 0;
	if (!str)
		return (NULL);
	re = malloc(whithout_q_count(str, x) + 1);
	while (str[x])
	{
		l = chacke_q(str[x], &q);
		if ((l == 1 && str[x] == '"') || (l == 2 && str[x] == '\''))
			re[c++] = str[x];
		else if (str[x] != '"' && str[x] != '\'')
			re[c++] = str[x];
		x++;
	}
	if (is_wildcardss)
		free(str);
	return (re[c] = '\0', re);
}
