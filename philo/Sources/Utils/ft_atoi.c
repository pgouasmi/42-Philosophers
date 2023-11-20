/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:18:15 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/20 14:47:08 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	check_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_atoi(const char *str)
{
	size_t	value;
	size_t	index;
	int		sign;

	value = 0;
	index = 0;
	sign = 1;
	while (check_space(str[index]))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign *= -1;
		index++;
	}
	while (check_number(str[index]))
	{
		value = (value * 10) + (str[index] - '0');
		index++;
	}
	return (value * sign);
}
