/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:27:17 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 19:28:46 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

// $? g_exit_status
static int	change_var_count_one(int *x)
{
	char	*str;
	int		i;

	str = ft_itoa(g_exit_status);
	i = ft_strlen(str);
	(*x)++;
	free(str);
	return (i);
}

int	check_doub(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '"')
			return (1);
		x++;
	}
	return (0);
}

static int	change_var_count_tow(char **envp, int l, int *x, char *str)
{
	int		j;
	char	*var;
	int		i;
	char	*ss;

	ss = get_name_var(str + *x, x);
	var = search_in_env(envp, ss);
	i = 0;
	free(ss);
	j = 0;
	while (var && var[j])
	{
		if (check_doub(var) && l == 2 && (var[j] == '"'))
			i++;
		else if (!l && (var[j] == '\'' || var[j] == '<' 
				|| var[j] == '>' || var[j] == '|' || var[j] == '"'))
			i += 2;
		i++;
		j++;
	}
	return (i);
}

// cat << $USER stoop in $USER not value of $USER
static int	count_check_and_her_var(char *str, int x, int j, int l )
{
	if (x > 0)
		x--;
	if (x > 0 && str[x] != '<' && str[x] != '>')
	{
		while (x >= 0)
		{
			if (is_sp(str[x]))
				break ;
			x--;
		}
	}
	if (str[j] == '$' && l != 1 && str[j + 1]
		&& !is_sp(str[j + 1]) && str[j + 1] != '$')
	{
		while (x >= 0)
		{
			if ((!l || (x > 0 && str[x - 1] == '<')) 
				&& (str[x] == '<' || str[x] == '>'))
				return (0);
			if (!is_sp(str[x--]))
				return (1);
		}
		return (1);
	}
	return (0);
}

int	change_var_count(char *str, char **envp)
{
	int		x;
	int		i;
	int		l;
	t_quote	q;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	x = -1;
	i = 0;
	while (str[++x])
	{
		l = chacke_q(str[x], &q);
		if (count_check_and_her_var(str, x, x, l))
		{
			if (str[x + 1] == '?')
				i = i + change_var_count_one(&x);
			else if (!(is_sp(str[x + 1]) || str[x + 1] == '\''
					|| str[x + 1] == '"'))
				i = i + (change_var_count_tow(envp, l, &x, str));
		}
		else
			i++;
	}
	return (i);
}
