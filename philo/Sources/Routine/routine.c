/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:37:18 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/13 19:36:19 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t to_sleep)
{
	size_t	value;

	value = get_time_ms();
	while (get_time_ms() - value < to_sleep)
	{
		usleep(100);
	}
}

void	print(char *to_display, t_philo *philo)
{
	size_t	time_value;

	time_value = get_time_ms() - philo->data->starttime;
	pthread_mutex_lock(&philo->data->print);
	printf("%zu %d %s\n", time_value, philo->id, to_display);
	pthread_mutex_unlock(&philo->data->print);

}

void	philo_eats(t_philo *philo)
{
	if (end_condition(philo))
		return ();
	pthread_mutex_lock(&philo->fork);
	if (end_condition(philo))
		return (pthread_mutex_unlock(&philo->fork));
	print("has taken a fork", philo);
	if (end_condition(philo))
	pthread_mutex_lock(&philo->next->fork);
	print("has taken a fork", philo);
	print("is eating", philo);
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->state_mutex);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->time_last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	}

void	philo_sleeps(t_philo *philo)
{
	if (!end_condition(philo))
	{
		philo->state = SLEEPING;
		print("is sleeping", philo);
		ft_usleep(philo->time_to_sleep);
	}
}

void	philo_thinks(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->fflag);
	// pthread_mutex_lock(&philo->data->dflag);
	if (!end_condition(philo))
	{
		// pthread_mutex_unlock(&philo->data->fflag);
		// pthread_mutex_unlock(&philo->data->dflag);
		print("is thinking", philo);
		pthread_mutex_lock(&philo->state_mutex);
		philo->state = THINKING;
		pthread_mutex_unlock(&philo->state_mutex);
	}
	// else
	// {
	// 	pthread_mutex_unlock(&philo->data->fflag);
	// 	pthread_mutex_unlock(&philo->data->dflag);
	// }
}

int get_flag(int type, t_philo *philo)
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

int		check_dead(t_data *data)
{
	t_philo *temp;
	int		i;
	size_t	gap;

	i = 0;
	temp = data->philos;
	while (i < data->philo_number)
	{
		pthread_mutex_lock(&temp->mutex_last_meal);
		gap = get_time_ms() - temp->time_last_meal;
		pthread_mutex_unlock(&temp->mutex_last_meal);
		if (gap >= temp->time_to_die)
		{
			update_flag(DFLAG, 1, data);
			print("died", temp);
			return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

int		have_eaten_all_meals(t_data *data)
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
	t_data *data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_dead(data))
			break ;
		if (have_eaten_all_meals(data))
			break ;
		ft_usleep(10);
	}
	return (arg);
}

void	threads_init(t_data *data, t_philo *lst, int philo_nbr)
{
	int		i;
	t_philo	*temp;

	i = 0;
	temp = lst;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->fflag, NULL);
	pthread_mutex_init(&data->dflag, NULL);
	pthread_create(&data->watcher, NULL, routine_watcher, data);
	while (i < philo_nbr)
	{
		if (pthread_create(&temp->thread, NULL, routine, temp))
			return (free_struct(data), exit(1));
		temp = temp->next;
		i++;
	}
	i = 0;
	pthread_join(data->watcher, NULL);
	while (i < philo_nbr)
	{
		if (pthread_join(temp->thread, NULL))
			return (free_struct(data), exit(1));
		temp = temp->next;
		i++;
	}
	return ;
}
