/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:15:15 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/14 14:22:05 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *to_display, t_philo *philo)
{
	size_t	time_value;

	time_value = get_time_ms() - philo->data->starttime;
	pthread_mutex_lock(&philo->data->print);
	printf("%zu %d %s\n", time_value, philo->id, to_display);
	pthread_mutex_unlock(&philo->data->print);
}

int	get_flag(int type, t_philo *philo)
{
	int	result;

	if (type == FFLAG)
	{
		pthread_mutex_lock(&philo->data->fflag);
		result = philo->data->full_flag;
		pthread_mutex_unlock(&philo->data->fflag);
		return (result);
	}
	pthread_mutex_lock(&philo->data->dflag);
	result = philo->data->dead_flag;
	pthread_mutex_unlock(&philo->data->dflag);
	return (result);
}

int	end_condition(t_philo *philo)
{
	if (get_flag(FFLAG, philo))
		return (1);
	if (get_flag(DFLAG, philo))
		return (1);
	return (0);
}
