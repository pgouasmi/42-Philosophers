/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:37:18 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/16 14:30:23 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo, t_philo *holding)
{
	while (holding->held_fflag)
		ft_usleep(10);
	pthread_mutex_lock(&holding->fork);
	holding->held_fflag = 1;
	if (end_condition(philo))
		return (1);
	print("has taken a fork", philo);
	pthread_mutex_unlock(&holding->fork);
	return (0);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo->held_fflag = 0;
	pthread_mutex_unlock(&philo->fork);
}

int	philo_eats(t_philo *philo)
{
	if (end_condition(philo))
		return (1);
	if (take_fork(philo, philo))
		return (pthread_mutex_unlock(&philo->fork));
	if (take_fork(philo, philo->next))
		return (pthread_mutex_unlock(&philo->fork),
			pthread_mutex_unlock(&philo->next->fork));
	if (end_condition(philo))
		return (pthread_mutex_unlock(&philo->fork),
			pthread_mutex_unlock(&philo->next->fork));
	print("is eating", philo);
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->time_last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	ft_usleep(philo->time_to_eat);
	drop_fork(philo);
	drop_fork(philo->next);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	return (0);
}

void	philo_sleeps(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->state_mutex);
	if (end_condition(philo))
		return ;
	print("is sleeping", philo);
	ft_usleep(philo->time_to_sleep);
}

void	philo_thinks(t_philo *philo)
{
	if (end_condition(philo))
		return ;
	print("is thinking", philo);
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
		ft_usleep(philo->time_to_eat - 10);
	while (!end_condition(philo))
	{
		if ((philo->id + i) % 2)
		{
			philo_eats(philo);
			philo_sleeps(philo);
		}
		if (philo->state != THINKING)
			philo_thinks(philo);
		i++;
	}
	return (philo);
}
