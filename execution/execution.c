/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 10:42:44 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/06 20:21:34 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	execution(t_args_n **cmd, t_env *env, t_fd fd)
{
	char	*path;

	if ((!opens_files((*cmd)->files))
		|| is_builtin(cmd, (*cmd)->arguments, env, fd))
		return ;
	fd.pid = fork();
	if (fd.pid == 0)
	{
		if (managing_input((*cmd)->inp, &fd, 2, NULL))
			dup2(fd.fd_in, STDIN_FILENO);
		if (managing_output((*cmd)->out, &fd, 2, NULL))
			dup2(fd.fd_out, STDOUT_FILENO);
		path = get_path((*cmd)->arguments[0], env->envp);
		if (!path)
		{
			free_env(&(env->env));
			ft_error(cmd, ": command not found\n", 127);
		}
		signal(SIGQUIT, SIG_DFL);
		execve(path, (*cmd)->arguments, env->envp);
		exit(EXIT_FAILURE);
	}
	wait_child(fd);
}

void	wait_children(int *fd, int *pids, int size, int i)
{
	int		status;
	bool	check;

	i = 0;
	check = true;
	while (i < size)
		close(fd[i++]);
	i = -1;
	while (++i < size)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			break ;
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			g_exit_status = WTERMSIG(status) + 128;
			if (g_exit_status == 131 && check)
				ctl_error("Quit: 3\n", &check);
		}
	}
	return (free(pids), free(fd));
}

void	controle_fd(t_args_n *cmd, t_args_n **cmds, t_fd fd)
{
	if (managing_input(cmd->inp, &fd, 2, NULL))
		change_fd_in(fd.fd_in, cmds);
	else if (fd.fd_in != 0)
		change_fd_in(fd.fd_in, cmds);
	close(fd.fd_in);
	if (managing_output(cmd->out, &fd, 2, NULL))
		change_fd_ouput(fd.fd_out, fd.fd_p[1]);
	else if (cmd->next)
		change_fd_ouput(fd.fd_p[1], fd.fd_p[0]);
	else
		change_fd_ouput(fd.save_out, fd.fd_p[1]);
	close(fd.fd_p[0]);
	close(fd.fd_out);
}

void	execute_child(t_args_n *cmd, t_args_n **cmds, t_env *env, t_fd fd)
{
	char	*path;

	path = NULL;
	if (!opens_files(cmd->files))
		exit(g_exit_status);
	controle_fd(cmd, cmds, fd);
	if (is_builtin(cmds, cmd->arguments, env, fd))
		exit(g_exit_status);
	path = get_path(cmd->arguments[0], env->envp);
	if (!path)
	{
		give_error(cmd);
		clear_history();
		clear_list(cmds);
		free_env(&(env->env));
		exit(127);
	}
	signal(SIGQUIT, SIG_DFL);
	execve(path, cmd->arguments, env->envp);
	exit(EXIT_FAILURE);
}

void	execut_(t_args_n **cmds, t_env *env, t_fd fd)
{
	int			*pids;
	int			*pipe_r;
	int			i;
	t_args_n	*cmd;

	i = 0;
	cmd = *cmds;
	pids = allocation_array(count_cmds(*cmds));
	pipe_r = allocation_array(count_cmds(*cmds));
	while (cmd)
	{
		pipe(fd.fd_p);
		fd.pid = fork();
		if (error_fork(fd, pipe_r, pids, count_cmds(*cmds)))
			break ;
		if (fd.pid == 0)
			execute_child(cmd, cmds, env, fd);
		pids[i++] = fd.pid;
		pipe_r[i - 1] = fd.fd_p[0];
		close(fd.fd_p[1]);
		fd.fd_in = fd.fd_p[0];
		cmd = (cmd)->next;
	}
	if (fd.pid > 0)
		wait_children(pipe_r, pids, i, i);
}
