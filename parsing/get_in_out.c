/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:19:17 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 11:58:54 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	count_i_o(t_files *files, int a, int b)
{
	int		i;
	int		x;

	x = 0;
	i = 0;
	while (files[i].last)
	{
		if (files[i].typ == a || files[i].typ == b)
			x++;
		i++;
	}
	return (x);
}

t_inp	*get_inp(t_files *files)
{
	t_inp	*in;
	int		i;
	int		x;

	in = malloc((count_i_o(files, 4, 3) + 1) * sizeof(t_inp));
	i = 0;
	x = 0;
	while (files[i].last)
	{
		if (files[i].typ == 4 || files[i].typ == 3)
		{
			in[x].inp = ft_strdup(files[i].file);
			if (files[i].typ == 4)
				in[x].is_h = true;
			else
				in[x].is_h = false;
			in[x].is_am = files[i].is_am;
			in[x].is_q = files[i].is_q;
			x++;
		}
		i++;
	}
	in[x].inp = NULL;
	in[x].is_h = false;
	return (in[x].is_am = false, in[x].is_q = false, in);
}

t_out	*get_out(t_files *files)
{
	t_out	*out;
	int		i;
	int		x;

	out = malloc((count_i_o(files, 1, 2) + 1) * sizeof(t_out));
	i = 0;
	x = 0;
	while (files[i].last)
	{
		if (files[i].typ == 1 || files[i].typ == 2)
		{
			out[x].out = ft_strdup(files[i].file);
			if (files[i].typ == 2)
				out[x].is_a = true;
			else
				out[x].is_a = false;
			out[x].is_am = files[i].is_am;
			x++;
		}
		i++;
	}
	out[x].out = NULL;
	out[x].is_a = false;
	out[x].is_am = false;
	return (out);
}
