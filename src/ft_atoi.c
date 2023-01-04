/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 20:57:24 by mrehberg          #+#    #+#             */
/*   Updated: 2022/12/21 08:14:10 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int character)
{
	if (character >= '0' && character <= '9')
		return (1);
	return (0);
}

static int	con_is_sign(char str_i)
{
	if (str_i == '-' || str_i == '+')
		return (1);
	return (0);
}

static int	control_sign(char str_i)
{
	if (str_i == '\r' || str_i == '\v' || str_i == '\f')
		return (1);
	if (str_i == '\n' || str_i == '\t' || str_i == ' ')
		return (1);
	return (0);
}

static	int	set_sign(const char *str, int *sign, int *i)
{
	if (str[*i] == '-' && ft_isdigit(str[*i + 1]))
	{
		*sign = -1;
		*i = *i + 1;
	}
	else if (str[*i] == '+' && ft_isdigit(str[*i + 1]))
	{
		*sign = 1;
		*i = *i + 1;
	}
	else if (str[*i] == '-' && !(ft_isdigit(*i + 1)))
		return (1);
	else
		*sign = 1;
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	while (control_sign(str[i]))
		i++;
	if (!(ft_isdigit(str[i]) || con_is_sign(str[i])))
		return (0);
	else
	{
		if (set_sign(str, &sign, &i))
			return (0);
		while (ft_isdigit(str[i]))
		{
			num = num * 10;
			num = num + (int)str[i] - '0';
			i++;
		}
	}
	return (num * sign);
}
