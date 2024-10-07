/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 07:47:23 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/03 10:58:48 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**full_path;

	i = -1;
	if (!cmd)
		return (NULL);
	if (check_is_dir(cmd, search_in_env(env, "PATH")))
		exit(126);
	full_path = ft_split(search_in_env(env, "PATH"), ':');
	if (access(cmd, X_OK) == 0 && ((!full_path) || (ft_strchr(cmd, '/'))))
		return (free_arrays(full_path), cmd);
	path = ft_strjoin("/", cmd);
	if (!full_path || ft_strcmp(path, "/") == 0 || ft_strchr(path, '.'))
		return (free(path), free_arrays(full_path), NULL);
	while (full_path[++i])
	{
		tmp = ft_strjoin(full_path[i], path);
		if (access(tmp, X_OK) == 0)
			break ;
		free(tmp);
		tmp = NULL;
	}
	return (free(path), free_arrays(full_path), tmp);
}

bool	controle_fd_blt(t_args_n *cmds, t_fd *fd)
{
	int		count;
	bool	flag;
	bool	check;

	flag = true;
	count = count_cmds(cmds);
	check = managing_input(cmds->inp, fd, count, &flag);
	if (flag == false)
		return (false);
	if (check)
		close(fd->fd_in);
	check = managing_output(cmds->out, fd, count, &flag);
	if (check && flag)
	{
		dup2(fd->fd_out, STDOUT_FILENO);
		close(fd->fd_out);
	}
	if (!flag)
		return (false);
	return (true);
}

bool	is_builtin(t_args_n **args, char **cmd, t_env *env, t_fd fd)
{
	int	count;

	count = count_cmds((*args));
	if (!cmd || !*cmd)
		return (false);
	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "echo")
		|| !ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "env")
		|| !ft_strcmp(cmd[0], "exit"))
	{
		if (count == 1)
		{
			if (controle_fd_blt(*args, &fd))
			{
				handle_blt(args, cmd, env);
				dup2(fd.save_out, STDOUT_FILENO);
			}
		}
		else
			handle_blt(args, cmd, env);
		return (true);
	}
	return (false);
}

void	handle_blt(t_args_n **args, char **cmd, t_env *env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		g_exit_status = change_directory(cmd, env->envp);
	else if (!ft_strcmp(cmd[0], "echo"))
		g_exit_status = echo_handling(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		g_exit_status = get_current_path();
	else if (!ft_strcmp(cmd[0], "export"))
	{
		env->check = true;
		g_exit_status = export_handling(cmd, &(env->env));
	}
	else if (!ft_strcmp(cmd[0], "unset"))
	{
		env->check = true;
		g_exit_status = unset_hadnling(&(env->env), cmd);
	}
	else if (!ft_strcmp(cmd[0], "env"))
		g_exit_status = print_env(env->env);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(args, cmd);
}
