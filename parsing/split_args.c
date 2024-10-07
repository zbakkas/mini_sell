/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:52:14 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/05 12:31:32 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

//1=>'  2=>"
int	chacke_q(char c, t_quote *q)
{
	if (c == '"' && !q->in_single_quote)
		q->in_double_quote = !q->in_double_quote;
	else if (c == '\'' && !q->in_double_quote)
		q->in_single_quote = !q->in_single_quote;
	if (!q->in_double_quote && !q->in_single_quote)
		return (0);
	else if (!q->in_double_quote && q->in_single_quote)
		return (1);
	else if (q->in_double_quote && !q->in_single_quote)
		return (2);
	else
		return (3);
}

static	int	c_word(char *s)
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
	while (is_sp(s[x]))
		x++;
	if (s[x] == '\0')
		return (0);
	while (s[x])
	{
		if (!chacke_q(s[x], &q) && is_sp(s[x]) && !is_sp(s[x + 1])
			&& x < ft_strlen(s) - 1)
			re++;
		x++;
	}
	return (re + 1);
}

static char	*word(char *s, int *x)
{
	int		i;
	char	*re;
	int		j;
	t_quote	q;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	i = 0;
	while (is_sp(s[*x]))
		(*x)++;
	while (s[(*x) + i])
	{
		if (!chacke_q(s[*x + i], &q) && is_sp(s[(*x) + i]))
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

char	**split_part(char *s)
{
	char	**re;
	int		x;
	int		j;
	int		t;

	x = 0;
	j = 0;
	if (!s)
		return (free(s), NULL);
	t = c_word(s);
	re = (char **)malloc((1 + t) * sizeof(char *));
	if (!re)
		return (NULL);
	while (j < t)
	{
		re[j] = word(s, &x);
		j++;
	}
	re[j] = NULL;
	free(s);
	return (re);
}

// int main()
// {
//     char *str0 ="ls \"\" -a \"\" -l";
//     char *str1 ="l\"s\"> \"hello  <'worde\"  \"-l -a\" \"\">\"\" 'out'";
//     char *str2 ="l\"s\"< 'hello  \">> worde'  \"-l -a\">> out >f";
//     char *str3 ="'cat'\"<\" \" min '2\" -e";
//     printf("%s\n",str3);
//    printf("%s\n", set_speece(str3));
// char ** str =split_part(set_speece(str3));
// int x =0;
// while (str[x])
// {
//     printf("%s\n",str[x]);
//     x++;
// }
// }