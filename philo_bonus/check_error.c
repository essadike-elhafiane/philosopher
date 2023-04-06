/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:34:18 by eelhafia          #+#    #+#             */
/*   Updated: 2023/03/15 00:56:04 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v'
		|| c == '\n' || c == '\f')
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	a;
	int		r;

	r = 1;
	a = 0;
	i = 0;
	while (ft_isspace(str[i]))
			i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-')
			r = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + str[i] - 48;
		i++;
	}
	return (a * r);
}

int	ft_str_isdigit(char *str)
{
	while (*str)
	{
		if (*str == '+')
			str++;
		if (!ft_isdigit(*str))
			return (0);
		while (ft_isdigit(*str))
			str++;
		if (*str == '-')
			return (0);
		if (*str == '+')
			return (0);
		if (*str == ' ')
			str++;
	}
	return (1);
}

int	ft_check_error(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_str_isdigit(av[i]))
			return (1);
		i++;
	}
	return (0);
}
