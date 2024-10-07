/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:45:21 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 19:28:33 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	is_her(char *str, int x)
{
	if (str[x] == '<' && str[x + 1] == '<')
		return (1);
	if (x - 1 >= 0 && str[x] == '<' && str[x - 1] == '<')
		return (1);
	return (0);
}

//$? g_exit_status
static void	change_var_one(int *x, char *re, int *i)
{
	char	*str;
	int		a;

	str = ft_itoa(g_exit_status);
	a = 0;
	while (str[a])
	{
		re[(*i)++] = str[a++];
	}
	free(str);
	(*x)++;
}

static void	change_var_tow(t_args_var *args, char *str, char **envp)
{
	int		j;
	char	*ss;
	char	*var;

	j = args->x;
	ss = get_name_var(str + args->x, &(*args).x);
	var = search_in_env(envp, ss);
	free(ss);
	j = 0;
	while (var && var[j])
	{
		if (check_doub(var) && args->l == 2 && (var[j] == '"'))
		{
			args->re[args->i++] = '"';
			args->re[args->i++] = var[j];
		}
		else if (!args->l && (var[j] == '\'' || var[j] == '<' 
				|| var[j] == '>' || var[j] == '|' || var[j] == '"'))
		{
			change_var_tow_one(args, var, j);
		}
		else
			args->re[args->i++] = var[j];
		j++;
	}
}

// cat << $USER stoop in $USER not value of $USER
static int	check_and_her_var(char *str, int x, t_args_var args)
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
	if (str[args.x] == '$' && args.l != 1 && str[args.x + 1]
		&& !is_sp(str[args.x + 1]) && str[args.x + 1] != '$')
	{
		while (x >= 0)
		{
			if ((!args.l || (x > 0 && str[x - 1] == '<'))
				&& (str[x] == '<' || str[x] == '>'))
				return (0);
			if (!is_sp(str[x--]))
				return (1);
		}
		return (1);
	}
	return (0);
}

// $arg < $arg < $ARG $arg
char	*change_var(char *str, char **envp)
{
	t_args_var	args;

	args.q.in_double_quote = 0;
	args.q.in_single_quote = 0;
	args.re = malloc (change_var_count(str, envp) + 1);
	args.x = -1;
	args.i = 0;
	while (str[++args.x])
	{
		args.l = chacke_q(str[args.x], &args.q);
		if (check_and_her_var(str, args.x, args))
		{
			if (str[args.x + 1] == '?')
				change_var_one(&args.x, args.re, &args.i);
			else if (!(is_sp(str[args.x + 1]) || str[args.x + 1] == '\''
					|| str[args.x + 1] == '"'))
				change_var_tow(&args, str, envp);
		}
		else
			args.re[args.i++] = str[args.x];
	}
	return (args.re[args.i] = '\0', args.re);
}
