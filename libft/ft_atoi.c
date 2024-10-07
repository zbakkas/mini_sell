/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:11:15 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/08/23 12:53:53 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(long long nb, int n)
{
	if ((nb >= 922337203685477580 && n > 7) || (nb < 0))
		return (1);
	return (0);
}

static int	convert(const char *str, int signe)
{
	int				i;
	int				cheack;
	long long		result;

	i = 0;
	result = 0;
	cheack = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		cheack = check(result, str[i] - 48);
		if (cheack == 1)
			result = result * 10 + (str[i] - 48);
		else
			return (cheack);
		i++;
	}
	return ((int)result * signe);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;

	i = 0;
	signe = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	return (convert(str + i, signe));
}

int	atoi_(char *str, int *flag)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (!str || !(str[i] >= '0' && str[i] <= '9'))
		*flag = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (check(result, (str[i] - '0')))
			*flag = 1;
		i++;
	}
	if (str[i] != '\0')
		*flag = 1;
	return (result * sign);
}

int	count_arrays(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
