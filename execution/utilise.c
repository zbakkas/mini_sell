/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:33:20 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/06 18:13:51 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	sorte_env(t_envp *head)
{
	t_envp	*next;
	char	*tmp;

	while (head)
	{
		next = head->next;
		while (next)
		{
			if (ft_strcmp(head->env, next->env) > 0)
			{
				tmp = head->env;
				head->env = next->env;
				next->env = tmp;
			}
			next = next->next;
		}
		head = head->next;
	}
}

t_envp	*search_env(t_envp *env, char *str)
{
	char	*s1;
	int		len_str;

	s1 = ft_strdup(str);
	s1[find_char(str, '=')] = '\0';
	len_str = ft_strlen(s1);
	if (s1[len_str - 1] == '+')
		len_str--;
	while (env)
	{
		if (ft_strncmp(env->env, s1, len_str) == 0 && (env->env[len_str] == '='
				|| !env->env[len_str]))
			return (free(s1), env);
		env = env->next;
	}
	free(s1);
	return (NULL);
}

bool	valid_unset(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	while (str[i])
	{
		if ((!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_'))
			return (false);
		i++;
	}
	return (true);
}

int	unset_hadnling(t_envp **env, char **cmd)
{
	int		i;
	bool	check;
	t_envp	*pos;

	i = 1;
	check = false;
	while (cmd[i])
	{
		if (!valid_unset(cmd[i]))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			check = true;
		}
		pos = search_env(*env, cmd[i]);
		unset(env, pos);
		i++;
	}
	return (check);
}

bool	adding_env(t_envp **env, char *str)
{
	t_envp	*pos;
	bool	status;

	status = true;
	if (!valid_export(str))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (false);
	}
	else
	{
		pos = search_env(*env, str);
		if (pos)
		{
			if (!valid_add(str) || !check_join(pos, &str))
				return (status);
			free(pos->env);
			pos->env = ft_strdup(str);
			return (status);
		}
		creat_list(env, str);
	}
	return (status);
}
