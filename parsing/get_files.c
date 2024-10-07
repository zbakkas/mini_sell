/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:49:05 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 11:44:05 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

typedef struct s_get_files_arg
{
	t_files	*file;
	int		c;
}	t_get_files_arg;

static int	get_files_count(char **str)
{
	int	x;
	int	c;

	x = 0;
	c = 0;
	while (str[x])
	{
		if (!ft_strncmp(str[x], "<", 2) || !ft_strncmp(str[x], "<<", 3) 
			|| !ft_strncmp(str[x], ">", 2) || !ft_strncmp(str[x], ">>", 3))
			c++;
		x++;
	}
	return (c);
}

static int	is_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

static void	get_files_v(t_get_files_arg	*arg, int typ, char *str, char **envp)
{
	if (typ == 4 && is_quote(str))
		arg->file[arg->c].is_q = true;
	else
		arg->file[arg->c].is_q = false;
	if (str && (!ft_strncmp(str, "<", 2) || !ft_strncmp(str, "<<", 3)
			|| !ft_strncmp(str, ">", 2) || !ft_strncmp(str, ">>", 3)))
	{
		free(str);
		str = NULL;
	}
	if (typ != 4 && check_ambiguous(str, envp))
		arg->file[arg->c].is_am = true;
	else
		arg->file[arg->c].is_am = false;
	if (typ != 4 && !check_ambiguous(str, envp))
		arg->file[arg->c].file = whithout_q(change_var(str, envp), 1);
	else
		arg->file[arg->c].file = whithout_q(str, 0);
	arg->file[arg->c].typ = typ;
	arg->file[arg->c].last = ft_strdup("1");
	(arg->c)++;
}
//> 1
//>> 2
//< 3
//<< 4

t_files	*get_files(char **str, char **envp)
{
	int				x;
	t_get_files_arg	arg;

	arg.file = malloc((get_files_count(str) + 1) * sizeof(t_files));
	arg.c = 0;
	x = 0;
	while (str[x])
	{
		if (!ft_strncmp(str[x], "<", 2) || !ft_strncmp(str[x], "<<", 3) 
			|| !ft_strncmp(str[x], ">", 2) || !ft_strncmp(str[x], ">>", 3))
		{
			if (!ft_strncmp(str[x], ">", 2))
				get_files_v(&arg, 1, str[x + 1], envp);
			else if (!ft_strncmp(str[x], ">>", 3))
				get_files_v(&arg, 2, str[x + 1], envp);
			else if (!ft_strncmp(str[x], "<", 2))
				get_files_v(&arg, 3, str[x + 1], envp);
			else if (!ft_strncmp(str[x], "<<", 3))
				get_files_v(&arg, 4, str[x + 1], envp);
		}
		x++;
	}
	arg.file[arg.c].last = NULL;
	return (arg.file[arg.c].typ = 0, arg.file[arg.c].file = NULL
		, arg.file[arg.c].is_am = false, arg.file);
}
