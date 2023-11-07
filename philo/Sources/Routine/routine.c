/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:37:18 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/07 17:09:31 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	(void)arg;
	return (NULL);
}

void	thread_init(t_data *data, t_philo *lst, int philo_nbr)
{
	int		i;
	t_philo	*temp;

	i = 0;
	temp = lst;
	while (i < philo_nbr)
	{
		if (pthread_create(&temp->thread, NULL, routine, data))
			return (free_struct(data), exit(1));
		if (pthread_join(temp->thread, NULL))
			return (free_struct(data), exit(1));
		temp = temp->next;
		i++;
	}
}

void	start_routine(t_data *data)
{
	thread_init(data, data->philos, data->philo_number);
}
