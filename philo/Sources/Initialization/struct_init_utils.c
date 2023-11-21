/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:28:39 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/21 14:11:15 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_errors(int type)
{
	if (type == 1)
		write(2, "Bad input : `Number_of_philosophers'\n", 38);
	else if (type == 2)
		write(2, "Bad input : `Time_to_die'\n", 27);
	else if (type == 3)
		write(2, "Bad input : `Time_to_eat'\n", 27);
	else if (type == 4)
		write(2, "Bad input : `Time_to_sleep'\n", 29);
	else if (type == 5)
	{
		write(2, "Bad input :", 12);
		write(2, "`Number_of_times_each_philosopher_must_eat'\n", 45);
	}
}

static int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	arg_has_wrong_char(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!is_num(str[i]))
			return (1);
		i++;
	}
	return (0);
}
