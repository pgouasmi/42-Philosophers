/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:37:18 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/09 18:49:22 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t to_sleep)
{
	size_t	value;

	value = get_time_ms();
	while (get_time_ms() - value < to_sleep)
	{
		usleep(10);
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
	pthread_mutex_lock(&philo->fork);
	print("has taken a fork", philo);
	pthread_mutex_lock(&philo->next->fork);
	print("has taken a fork", philo);
	print("is eating", philo);
	philo->meals_eaten++;
	philo->state = EATING;
	ft_usleep(philo->time_to_eat);
	philo->time_last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	philo_sleeps(t_philo *philo)
{
	print("is_sleeping", philo);
	ft_usleep(philo->time_to_sleep);
}

void	philo_thinks(t_philo *philo)
{
	print("is thinking", philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	if (!philo->id % 2)
		ft_usleep(50);
	while (!*(philo)->dead_flag)
	{
		philo_eats(philo);
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	return (philo);
}

int		check_dead(t_data *data)
{
	t_philo *temp;
	size_t	gap;
	int		i;

	i = 0;
	temp = data->philos;
	// printf("gettime = %zu\n", get_time_ms());
	// printf("last meal = %zu\n", temp->time_last_meal);
	// printf("gap = %zu\n", gap);
	while (i < data->philo_number)
	{
		gap = get_time_ms() - temp->time_last_meal;
		if (gap >= temp->time_to_die)
		{
			data->dead_flag = 1;
			printf("gettime = %zu\n", get_time_ms());
			printf("last meal = %zu\n", temp->time_last_meal);
			printf("gap = %zu\n", gap);
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
		if (temp->meals_eaten < data->meals_to_eat)
			return (0);
		i++;
		temp = temp->next;
	}
	return (1);
}

void	*routine_watcher(void *arg)
{
	t_data *data;
	
	data = (t_data *)arg;
	while (1)
	{
		if (check_dead(data) || have_eaten_all_meals(data))
			return (free_struct(data), exit(0), arg);
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
}
