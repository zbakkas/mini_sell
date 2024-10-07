/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:49:03 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/23 18:11:22 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static int	check(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*new_str;
	int		x;

	start = 0;
	if (!s1)
		return (NULL);
	else if (!set && s1)
		return ((char *)s1);
	end = ft_strlen(s1);
	while (s1[start] && check(s1[start], (char *)set))
		start++;
	while (check(s1[end - 1], (char *)set) && end > start)
		end--;
	new_str = ft_substr(s1, start, end - start);
	if (!new_str)
		return (NULL);
	return (new_str);
}*/
static int	chick(char s, char const *set)
{
	int	x;

	x = 0;
	while (set[x])
	{
		if (s == set[x])
			return (1);
		x++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set, int l)
{
	char	*re;
	int		star;
	int		end;

	if (!s1)
		return (NULL);
	if (l)
	{
		re = ft_strdup(s1);
		return (re);
	}
	star = 0;
	end = ft_strlen(s1);
	while (s1[star] && chick(s1[star], set))
		star++;
	while (s1[end - 1] && chick(s1[end - 1], set))
		end--;
	if (end > star)
		re = ft_substr(s1, star, end - star);
	else
		re = ft_substr(s1, star, star - end);
	return (re);
}
