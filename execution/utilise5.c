/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:31:27 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/09/06 19:20:03 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

//> 1
//>> 2
//< 3
//<< 4

bool	opens_files(t_files *file)
{
	int	i;
	int	fd;

	i = -1;
	fd = -2;
	while (file[++i].last)
	{
		if (file[i].is_am)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(file[i].file, STDERR_FILENO);
			ft_putendl_fd(ERR_AMBG, STDERR_FILENO);
			return (g_exit_status = 1, false);
		}
		if (file[i].typ == 1 && !file[i].is_am)
			fd = open(file[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (file[i].typ == 2 && !file[i].is_am)
			fd = open(file[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file[i].typ == 3 && !file[i].is_am)
			fd = open(file[i].file, O_RDONLY);
		if (fd == -1)
			return (error_files(file[i].file), g_exit_status = 1, false);
		close(fd);
	}
	return (true);
}

bool	check_join(t_envp *pos, char **str)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	tmp = ft_strchr(*str, '+');
	tmp1 = ft_strchr(*str, '=');
	if (tmp && tmp1)
	{
		if (tmp < tmp1)
		{
			tmp = pos->env;
			tmp2 = ft_strchr(tmp, '=');
			if (tmp2)
				tmp1 = tmp1 + 1;
			pos->env = ft_strjoin(pos->env, tmp1);
			free(tmp);
			return (false);
		}
	}
	return (true);
}
