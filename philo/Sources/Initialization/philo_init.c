/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:53:17 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/13 18:08:38 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_new_philo(t_data *data, t_philo *new)
{
	new->meals_eaten = 0;
	new->time_to_die = (size_t)data->time_to_die;
	new->time_to_eat = (size_t)data->time_to_eat;
	new->time_to_sleep = (size_t)data->time_to_eat;
	new->meals_to_eat = data->meals_to_eat;
	new->data = data;
	new->state = INIT;
	new->dead_flag = &data->dead_flag;
	new->full_flag = &data->full_flag;
	pthread_mutex_init(&new->fork, NULL);
	pthread_mutex_init(&new->mutex_last_meal, NULL);
	pthread_mutex_init(&new->state_mutex, NULL);
	pthread_mutex_init(&new->meals_eaten_mutex, NULL);
	new->time_last_meal = get_time_ms();
}

static void	create_philo(t_data *data, t_philo **lst, int philo_id)
{
	t_philo	*new;
	t_philo	*temp;

	new = malloc(sizeof(*new));
	if (!new)
		return (free_struct(data), exit(1));
	new->id = philo_id;
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	if (philo_id == data->philo_number)
		new->next = *lst;
	else
		new->next = NULL;
	init_new_philo(data, new);
}

void	philo_init(t_data *data)
{
	int	i;

	data->philos = NULL;
	i = 0;
	while (i < data->philo_number)
	{
		create_philo(data, &data->philos, i + 1);
		i++;
	}
}
