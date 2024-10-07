/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:40:48 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/05 12:31:32 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static	int	c_word( char *s, char c)
{
	size_t	x;
	int		re;
	t_quote	q;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	x = 0;
	re = 0;
	if (!s[x])
		return (0);
	if (s[x] && c == '\0')
		return (1);
	x = 0;
	if (s[x] == '\0')
		return (0);
	while (s[x])
	{
		if (!chacke_q(s[x], &q) && c == s[x] && c != s[x + 1])
			re++;
		x++;
	}
	return (re + 1);
}

static	char	**is_free(char **d)
{
	int	x;

	x = 0;
	while (d[x])
	{
		free(d[x]);
		x++;
	}
	free(d);
	return (NULL);
}

static char	*word(char *s, char c, int *x)
{
	int		i;
	char	*re;
	int		j;
	t_quote	q;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	i = 0;
	while (s[*x] == c)
		(*x)++;
	while (s[(*x) + i])
	{
		if (!chacke_q(s[(*x) + i], &q) && s[(*x) + i] == c)
			break ;
		i++;
	}
	re = malloc (i + 1);
	if (!re)
		return (NULL);
	j = 0;
	while (i > j)
		re[j++] = s[(*x)++];
	re[j] = '\0';
	return (re);
}

char	**ft_split_pip(char *s, char c)
{
	char	**re;
	int		x;
	int		j;
	int		t;

	x = 0;
	j = 0;
	if (!s)
		return (NULL);
	t = c_word(s, c);
	re = (char **)malloc((1 + t) * sizeof(char *));
	if (!re)
		return (NULL);
	while (j < t)
	{
		re[j] = word(s, c, &x);
		if (!re[j])
			return (is_free(re));
		j++;
	}
	re[j] = NULL;
	return (re);
}

// char **get_parts_by_pip(char *str)
// {
//     char **re;
//     re = ft_split(str,'|');
//     return re;
// }
// int main ()
// {
//     int x =0;
// 	char *str ="> out cat -e out1 | wc -c" ;
// 	printf("cmd = %s\n",str);
//     while (ft_split_pip(str,'|')[x])
//     {
//     	printf("%s\n",ft_split_pip(str ,'|')[x]);
//         x++;
//     }
// }
