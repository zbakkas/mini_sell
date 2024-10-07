/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_speace_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:40:50 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/05 12:31:32 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	is_sp(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

//re+=2 >> add after and befor
int	set_speece_count(char *str)
{
	int		x;
	t_quote	q;
	int		re;

	x = 0;
	q.in_double_quote = 0;
	q.in_single_quote = 0;
	re = ft_strlen(str);
	while (str[x])
	{
		if (!chacke_q(str[x], &q) && (str[x] == '>' || str[x] == '<'))
		{
			re += 2;
			while (str[x] == '>' || str[x] == '<')
				x++;
		}
		else
			x++;
	}
	return (re);
}

char	*set_speece(char *str)
{
	char	*re;
	int		x;
	int		i;
	t_quote	q;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	re = malloc(set_speece_count(str) + 1);
	x = 0;
	i = 0;
	while (str[x])
	{
		if (!chacke_q(str[x], &q) && (str[x] == '>' || str[x] == '<'))
		{
			re[i++] = ' ';
			while (str[x] == '>' || str[x] == '<')
				re[i++] = str[x++];
			re[i++] = ' ';
		}
		else
			re[i++] = str[x++];
	}
	re[i] = '\0';
	return (re);
}
