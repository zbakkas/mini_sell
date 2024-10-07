/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:37:16 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 10:47:08 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	remove_file(t_inp *inp);

void	clear_in_ou(t_args_n **lst)
{
	int	i;

	i = 0;
	while ((*lst)->inp[i].inp)
		free((*lst)->inp[i++].inp);
	free((*lst)->inp);
	(*lst)->inp = NULL;
	i = 0;
	while ((*lst)->out[i].out)
		free((*lst)->out[i++].out);
	free((*lst)->out);
	(*lst)->out = NULL;
	i = 0;
	while ((*lst)->files[i].last)
	{
		free((*lst)->files[i].file);
		free((*lst)->files[i].last);
		i++;
	}
	free((*lst)->files);
	(*lst)->files = NULL;
}

void	clear_list(t_args_n **lst)
{
	t_args_n	*nexttte;
	int			i;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		i = 0;
		remove_file((*lst)->inp);
		nexttte = (*lst)->next;
		while ((*lst)->arguments[i])
			free((*lst)->arguments[i++]);
		free((*lst)->arguments);
		(*lst)->arguments = NULL;
		clear_in_ou(lst);
		i = 0;
		free(*lst);
		*lst = nexttte;
	}
	*lst = NULL;
}

char	*strjoin_parsing(char *start, char *buff)
{
	char	*re;
	int		xx;
	int		x;

	x = 0;
	xx = 0;
	if (!start)
	{
		start = malloc(1);
		start[0] = '\0';
	}
	if (!start || !buff)
		return (0);
	re = malloc(ft_strlen(start) + ft_strlen(buff) + 1);
	if (!re)
		return (NULL);
	while (start[x])
		re[xx++] = start[x++];
	x = 0;
	while (buff[x])
		re[xx++] = buff[x++];
	re[xx] = '\0';
	free(start);
	return (re);
}
