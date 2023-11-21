/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:06:26 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/21 13:31:37 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_flag(int type, int val, t_data *data)
{
	if (type == DFLAG)
	{
		pthread_mutex_lock(&data->dflag);
		data->dead_flag = val;
		pthread_mutex_unlock(&data->dflag);
	}
	if (type == FFLAG)
	{
		pthread_mutex_lock(&data->fflag);
		data->full_flag = val;
		pthread_mutex_unlock(&data->fflag);
	}
}

int	check_dead(t_data *data)
{
	t_philo	*temp;
	int		i;
	size_t	gap;

	i = 0;
	temp = data->philos;
	while (i < data->philo_number)
	{
		pthread_mutex_lock(&temp->mutex_last_meal);
		gap = get_time_ms() - temp->time_last_meal;
		pthread_mutex_unlock(&temp->mutex_last_meal);
		if (gap > temp->time_to_die)
		{
			update_flag(DFLAG, 1, data);
			print("died", temp, DEAD);
			return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

int	have_eaten_all_meals(t_data *data)
{
	t_philo	*temp;
	int		i;

	if (data->meals_to_eat < 0)
		return (0);
	i = 0;
	temp = data->philos;
	while (i < data->philo_number)
	{
		pthread_mutex_lock(&temp->meals_eaten_mutex);
		if (temp->meals_eaten < data->meals_to_eat)
			return (pthread_mutex_unlock(&temp->meals_eaten_mutex), 0);
		pthread_mutex_unlock(&temp->meals_eaten_mutex);
		i++;
		temp = temp->next;
	}
	update_flag(FFLAG, 1, data);
	return (1);
}

void	*routine_watcher(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_dead(data))
			break ;
		if (have_eaten_all_meals(data))
			break ;
		usleep(10);
	}
	return (arg);
}
