/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:15:15 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/20 14:34:33 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo, t_philo *holding)
{
	int	flag;

	flag = 1;
	while (flag)
	{
		if (end_condition(philo))
			return (1);
		pthread_mutex_lock(&holding->fork);
		flag = holding->held_fflag;
		if (!flag)
			holding->held_fflag = 1;
		pthread_mutex_unlock(&holding->fork);
		usleep(1);
	}
	if (end_condition(philo))
		return (1);
	print("has taken a fork", philo, -1);
	return (0);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo->held_fflag = 0;
	pthread_mutex_unlock(&philo->fork);
}

void	print(char *to_display, t_philo *philo, int type)
{
	if (type == DEAD)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%zu %zu %s\n", get_time_ms() - philo->data->starttime,
			philo->id, to_display);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	pthread_mutex_lock(&philo->data->print);
	if (!end_condition(philo))
		printf("%zu %zu %s\n", get_time_ms() - philo->data->starttime,
			philo->id, to_display);
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
