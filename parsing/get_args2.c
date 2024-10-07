/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zouhirbakkas@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:50:38 by zbakkas           #+#    #+#             */
/*   Updated: 2024/09/06 12:04:20 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	get_args_count_if(char **str, int x)
{
	if (str[x + 1] && (ft_strncmp(str[x], "<", 2) == 0
			|| ft_strncmp(str[x], ">", 2) == 0
			|| ft_strncmp(str[x], "<<", 3) == 0
			|| ft_strncmp(str[x], ">>", 3) == 0))
		return (1);
	return (0);
}

static int	get_args_count(char **str)
{
	int		x;
	int		c;
	char	**ss; 

	x = -1;
	c = 0;
	while (str[++x])
	{
		if (get_args_count_if(str, x))
			x++;
		else if (check_wildcards(str[x]))
		{
			ss = get_name_of_files(str[x]);
			if (ft_strlen_doubl(ss) > 0)
				c += ft_strlen_doubl(ss);
			else
				c++;
			free_double_str(ss);
		}
		else
			c++;
	}
	return (c);
}

static void	grt_arg_one(char **str, int x, char **re, int *c)
{
	char	**ss;
	int		j;

	j = 0;
	ss = get_name_of_files((str[x]));
	if (ft_strlen_doubl(ss) > 0)
	{
		j = 0;
		while (ss[j])
			re[(*c)++] = ss[j++];
	}
	else
		re[(*c)++] = whithout_q(str[x], 0);
	free(ss);
}

char	**get_args(char **str)
{
	char	**re;
	int		x;
	int		c;

	x = 0;
	c = 0;
	re = (char **)malloc((get_args_count(str) + 1) * sizeof(char *));
	while (str[x])
	{
		if ((ft_strncmp(str[x], "<", 2) == 0
				|| ft_strncmp(str[x], ">", 2) == 0
				|| ft_strncmp(str[x], "<<", 3) == 0
				|| ft_strncmp(str[x], ">>", 3) == 0))
			x++;
		else if (check_wildcards(str[x]))
		{
			grt_arg_one(str, x, re, &c);
		}
		else
			re[c++] = whithout_q(str[x], 0);
		if (str[x])
			x++;
	}
	re[c] = NULL;
	return (re);
}

// int main()
// {
//     char *str0 ="ls \"\" -a \"\" -l";
//     char *str1 ="l\"s\"> \"hello  <'worde\"  \"-l -a\" \"\">\"\" 'out'";
//     char *str2 ="l\"s\"< 'hello  \">> worde'  \"-l -a\">> out >f";
//     char *str3 ="<'cat'\"<\" \" min '2\" \"-e\"";
//     char *str4 = "'ca't file >out >>out1<< stop out2 > out3 \"-e\" -l";
//     char *str5 ="ls";
//     printf("%s\n",str5);
// //    printf("%s\n", set_speece(str3));
// char ** str =split_part(set_speece(str5));
// int x =0;
// // while (str[x])
// // {
// //     printf("%s\n",str[x]);
// //     x++;
// // }
// // // printf("x==%d\n",x);
// // // printf("--------------------\n");
// // // printf("cmd=%s\n",get_cmd2(str) ? get_cmd2(str):"(null)");
// // // char **flags=get_flags2(str);
// // // x =0;
// // // while (flags && flags[x])
// // // {
// // //     printf("flag%d =%s\n",x,flags[x]);
// // //     x++;
// // // }
// // x =0;
// // char **args =get_args(str); 
// // while (args[x])
// // {
// //     printf("arg[%d]=%s\n",x,args[x]);
// //    x++;
// // }
// // // get_args(str);
// // // printf("%s\n" , whithout_q("    cat ffr"));
// // x =0;
// t_out *out =get_out(str);
// while (out[x].out)
// {
//     printf("out file [%d]:%s\n",x,out[x].out);
//     printf("is append [%d]:%d\n",x,out[x].is_a);
//     x++;
// }
// x =0;
// t_files *inp =get_files(str);
// while (inp[x].inp)
// {
//     printf("inp file [%d]:%s\n",x,inp[x].inp);
//     printf("is Heredoc [%d]:%d\n",x,inp[x].is_h);
//     x++;
// }
// }