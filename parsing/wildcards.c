/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:37:51 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 12:02:28 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

typedef struct s_wildcards_arg
{
	t_quote	q;
	int		x;
	int		l;
	int		i;

}			t_wildcards_arg;

static int	first_wildcards(char *str, int x)
{
	t_quote	q;
	int		l;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	while (x >= 0)
	{
		l = chacke_q(str[x], &q);
		if (!l && str[x] == '*')
			return (0);
		x--;
	}
	return (1);
}

static int	is_equal_one(char *str, char *name, t_wildcards_arg *args)
{
	char	*ss;

	if (!args->l && str[args->x] == '*' && args->x - 1 >= 0 && args->i != -1)
	{
		ss = whithout_q(chech_be(str, args->x), 1);
		if (!first_wildcards(str, args->x - 1) && ch_m(ss, name, &args->i))
			return (free(ss), 0);
		else if (first_wildcards(str, args->x - 1) && ch_f(ss, name, &args->i))
			return (free(ss), 0);
		free(ss);
	}
	else if (args->i == -1)
	{
		ss = whithout_q(check_aft(str, args->x, args->x), 1);
		if (ch_l(ss, name))
			return (free(ss), 0);
		free(ss);
	}
	if (!args->l && last_wildcards(str, args->x) == 2)
		args->i = -1;
	return (1);
}

//'h'*p*r*kv*'*' ===> hkonmpiirnvkv*
static int	is_equal(char *str, char *name)
{
	t_wildcards_arg	args;

	args.i = 0;
	args.x = 0;
	args.q.in_double_quote = 0;
	args.q.in_single_quote = 0;
	while (str[args.x])
	{
		args.l = chacke_q(str[args.x], &args.q);
		if (!is_equal_one(str, name, &args))
			return (0);
		args.x++;
	}
	return (1);
}

char	**get_name_of_files(char *str)
{
	struct dirent	*entry;
	DIR				*dp;
	char			*str_j;
	char			**re;

	re = NULL;
	str_j = NULL;
	dp = opendir(".");
	entry = readdir(dp);
	while (entry != NULL)
	{
		if (entry && entry->d_name[0] != '.' && is_equal(str, entry->d_name))
		{
			str_j = strjoin_parsing(str_j, entry->d_name);
			str_j = strjoin_parsing(str_j, "/");
		}
		entry = readdir(dp);
	}
	re = ft_split(str_j, '/');
	swapp(ft_strlen_doubl(re), re);
	free(str_j);
	closedir(dp);
	return (re);
}

int	check_wildcards(char *str)
{
	t_quote	q;
	int		x;
	int		l;

	x = 0;
	q.in_double_quote = 0;
	q.in_single_quote = 0;
	while (str[x])
	{
		l = chacke_q(str[x], &q);
		if (str[x] == '*' && !l)
			return (1);
		x++;
	}
	return (0);
}
