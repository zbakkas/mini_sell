/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:21:41 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 11:24:01 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

typedef struct s_args_var_err
{
	int		x;
	int		l;
	char	*re;
	char	add[2];
	t_quote	q;
}	t_args_var_err;

static int	check_speace_in_var(char *var)
{
	int	ll;
	int	s;

	ll = 0;
	s = 0;
	while (var && is_sp(var[ll]))
		ll++;
	while (var && var[ll])
	{
		if (var[ll] && s)
			return (1);
		ll++;
		while (var[ll] && is_sp(var[ll]))
		{
			ll++;
			s = 1;
		}
	}
	return (0);
}

//$hhbhb@fh$USER

int	is_all_space(char *str)
{
	int	x;

	x = 0;
	if (!str)
		return (0);
	while (is_sp(str[x]))
	{
		x++;
	}
	if (!str[x])
		return (1);
	return (0);
}

static int	check_ambiguous_one(char *str, char **envp, t_args_var_err *args)
{
	char	*var;
	char	*ss;

	args->l = chacke_q(str[args->x], &args->q);
	if (!args->l && str[args->x] == '$' && str[args->x + 1] 
		&& !is_sp(str[args->x + 1]) && str[args->x + 1] != '$')
	{
		ss = get_name_var(str + args->x, &args->x);
		var = search_in_env(envp, ss);
		if (!is_all_space(var))
		{
			if (check_speace_in_var(var))
				return (free(ss), free(args->re), 1);
			if (var)
				args->re = strjoin_parsing(args->re, var);
		}
		free(ss);
	}
	else
	{
		args->add[0] = str[args->x];
		args->add[1] = '\0';
		args->re = strjoin_parsing(args->re, args->add);
	}
	return (0);
}

int	check_ambiguous(char *str, char **envp)
{
	t_args_var_err	args;

	if (!str)
		return (0);
	args.x = 0;
	args.re = NULL;
	args.q.in_double_quote = 0;
	args.q.in_single_quote = 0;
	while (str[args.x])
	{
		if (check_ambiguous_one(str, envp, &args))
			return (1);
		args.x++;
	}
	if (!args.re)
		return (free(args.re), 1);
	return (free(args.re), 0);
}

char	*check_erroe_var(char *str, int x )
{
	int		i; 
	char	*re;
	char	add[2];
	int		l;
	t_quote	q;

	q.in_double_quote = 0;
	q.in_single_quote = 0;
	i = 0;
	re = NULL;
	x++;
	while (is_sp(str[x]))
		x++;
	while (str[x])
	{
		l = chacke_q(str[x], &q);
		if (!l && (is_sp(str[x]) || str[x] == '<' || str[x] == '>'))
			break ;
		add[0] = str[x];
		add[1] = '\0';
		re = strjoin_parsing(re, add);
		x++;
	}
	return (re);
}
