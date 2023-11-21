/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:13:43 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/20 12:41:57 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t to_sleep, t_philo *philo)
{
	size_t	value;

	value = get_time_ms();
	while (get_time_ms() - value < to_sleep)
	{
		if (!end_condition(philo))
			usleep(100);
		else
			return ;
	}
}
