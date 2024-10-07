/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:59:58 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 12:04:48 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	free_double_str(char **str)
{
	int	x;

	x = 0;
	if (!str)
		return ;
	while (str[x])
	{
		free(str[x++]);
	}
	free(str);
	str = (NULL);
}

t_args_n	*ft_lstnew_one(char **str, char **envp)
{
	t_args_n	*new_node;

	new_node = malloc(sizeof(t_args_n));
	if (!new_node)
		return (NULL);
	new_node->arguments = get_args(str);
	new_node->files = get_files(str, envp);
	new_node->inp = get_inp(new_node->files);
	new_node->out = get_out(new_node->files);
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_backk(t_args_n **lst, t_args_n *new)
{
	t_args_n	*re;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	re = *lst;
	while (re->next)
	{
		re = re->next;
	}
	re->next = new;
	lst = &re;
}

t_args_n	*initialization_list(char *line, char **envp)
{
	t_args_n	*list;
	int			x;
	char		*change_var_str;
	char		**split_p;
	char		**str;

	list = NULL;
	x = 0;
	if (!line || !line[0])
		return (NULL);
	change_var_str = change_var(line, envp);
	if (check_errors(line, x))
		return (free(change_var_str), NULL);
	split_p = ft_split_pip(change_var_str, '|');
	free(change_var_str);
	x = 0;
	while (split_p[x])
	{
		str = split_part(set_speece(split_p[x]));
		ft_lstadd_backk(&list, ft_lstnew_one(str, envp));
		free_double_str(str);
		x++;
	}
	free_double_str(split_p);
	return (list);
}
