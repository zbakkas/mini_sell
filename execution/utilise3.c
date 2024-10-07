/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:01:33 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/06 20:40:34 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	error_files(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (!ft_strcmp(file, ""))
		ft_putstr_fd(": ", STDERR_FILENO);
	perror(file);
}

void	give_error(t_args_n *cmd)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", cmd->arguments[0]);
	if (cmd->arguments && cmd->arguments[0] && *cmd->arguments[0])
		str = ft_strjoin(tmp, " :command not found\n");
	else
		str = ft_strjoin(tmp, ":command not found\n");
	ft_putstr_fd(str, STDERR_FILENO);
	free(str);
	free(tmp);
}

void	ctl_error(char *msg, bool *check)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	*check = false;
}

bool	error_fork(t_fd fd, int *pipe, int *pids, int size)
{
	int	i;

	i = 0;
	if (fd.pid < 0)
	{
		while (i < size)
		{
			if (pipe[i] != 0)
				close(pipe[i]);
			i++;
		}
		close(fd.fd_p[0]);
		close(fd.fd_p[1]);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror("fork");
		g_exit_status = 1;
		return (free(pipe), free(pids), true);
	}
	return (false);
}

void	unset(t_envp **env, t_envp *pos)
{
	t_envp	*prev;
	t_envp	*next;

	if (pos && size_env(*env) == 1)
		return (free(pos->env), free(pos), (*env) = NULL, free(NULL));
	else if (pos && pos == *env)
	{
		(*env) = pos->next;
		(*env)->prev = NULL;
		return (free(pos->env), free(pos));
	}
	else if (pos)
	{
		prev = pos->prev;
		next = pos->next;
		if (prev)
			prev->next = next;
		if (next)
			next->prev = prev;
		return (free(pos->env), free(pos));
	}
}
