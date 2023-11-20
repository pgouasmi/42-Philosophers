/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:37:18 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/20 14:28:15 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *philo)
{
	if (end_condition(philo))
		return ;
	if (take_fork(philo, philo))
		return ;
	if (take_fork(philo, philo->next))
		return ;
	if (end_condition(philo))
		return ;
	print("is eating", philo, -1);
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->time_last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	ft_usleep(philo->time_to_eat, philo);
	drop_fork(philo);
	drop_fork(philo->next);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
}

void	philo_sleeps(t_philo *philo)
{
	if (end_condition(philo))
		return ;
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->state_mutex);
	if (end_condition(philo))
		return ;
	print("is sleeping", philo, -1);
	ft_usleep(philo->time_to_sleep, philo);
}

void	philo_thinks(t_philo *philo)
{
	if (end_condition(philo))
		return ;
	print("is thinking", philo, -1);
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->state_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	size_t	i;

	i = 0;
	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		ft_usleep(philo->time_to_eat - 10, philo);
	while (!end_condition(philo))
	{
		if ((philo->id + i) % 2)
		{
			philo_eats(philo);
			philo_sleeps(philo);
		}
		else
			philo_thinks(philo);
		i++;
	}
	return (philo);
}
