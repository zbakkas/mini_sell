/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:06:15 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/03 10:16:35 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	creat_list(t_envp **envp, char *line)
{
	t_envp	*ptr;
	t_envp	*new_env;

	if (!envp)
		return ;
	new_env = (t_envp *)malloc(sizeof(t_envp));
	if (!new_env)
		return ;
	new_env->env = ft_strdup(line);
	new_env->next = NULL;
	if (!*envp)
	{
		*envp = new_env;
		(*envp)->prev = NULL;
		return ;
	}
	ptr = *envp;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new_env;
	new_env->prev = ptr;
}

void	parsing_env(t_envp **env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		creat_list(env, envp[i]);
		i++;
	}
}

bool	managing_input(t_inp *input, t_fd *fd, int count, bool *flag)
{
	int	i;

	i = 0;
	if (!input->inp)
		return (false);
	while (input[i].inp)
	{
		if (fd->fd_in != fd->save_in)
			close(fd->fd_in);
		fd->fd_in = open(input[i].inp, O_RDONLY);
		if (fd->fd_in < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			if (!ft_strcmp(input[i].inp, ""))
				ft_putstr_fd(": ", STDERR_FILENO);
			perror(input[i].inp);
			if (count > 1)
				exit(EXIT_FAILURE);
			else
				*flag = false;
			return (false);
		}
		i++;
	}
	return (true);
}

bool	managing_output(t_out *output, t_fd *fd, int count, bool *flag)
{
	int	i;

	i = -1;
	if (!output->out)
		return (false);
	while (output[++i].out)
	{
		if (fd->fd_out != fd->save_out)
			close(fd->fd_out);
		if (output[i].is_a)
			fd->fd_out = open(output[i].out, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			fd->fd_out = open(output[i].out, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (fd->fd_out < 0)
		{
			error_files(output[i].out);
			if (count > 1)
				exit(EXIT_FAILURE);
			else
				*flag = false;
		}
	}
	return (true);
}
