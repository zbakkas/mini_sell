/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise_blt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:46:55 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/06 19:18:33 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_exit(t_args_n **args, char **cmd)
{
	int	flag;
	int	status;

	flag = 0;
	status = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (count_arrays(cmd) >= 2)
	{
		status = atoi_(cmd[1], &flag);
		if (flag == 1)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (clear_list(args), close(3), close(4), exit(255));
		}
		else if (count_arrays(cmd) > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			g_exit_status = EXIT_FAILURE;
			return ;
		}
		exit(status);
	}
	return (clear_list(args), close(3), close(4), exit(g_exit_status));
}

int	print_env(t_envp *envp)
{
	char	*tmp;

	if (!envp)
		return (0);
	while (envp)
	{
		tmp = ft_strchr(envp->env, '=');
		if (tmp)
			ft_putendl_fd(envp->env, STDOUT_FILENO);
		envp = envp->next;
	}
	return (0);
}

void	print_export(t_envp *envp)
{
	int		j;
	bool	check;

	sorte_env(envp);
	while (envp)
	{
		j = 0;
		check = true;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (envp->env[j])
		{
			if (envp->env[j] == '=' && check == true)
			{
				write(STDOUT_FILENO, "=\"", 2);
				check = false;
			}
			else
				write(1, &envp->env[j], STDOUT_FILENO);
			j++;
		}
		if (ft_strchr(envp->env, '='))
			ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		envp = envp->next;
	}
}

int	size_env(t_envp *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (count);
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char	*handle_var(char *re, char *line, int *x, t_env *env)
{
	char	*ss;
	char	*var;

	ss = get_name_var(line + *x, x);
	var = search_in_env(env->envp, ss);
	if (var)
		re = strjoin(re, var);
	free(ss);
	return (re);
}
