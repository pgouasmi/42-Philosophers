/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:10:50 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/21 14:14:29 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_init(t_data *data, t_philo *lst, int philo_nbr)
{
	int		i;
	t_philo	*temp;

	i = 0;
	temp = lst;
	if (pthread_create(&data->watcher, NULL, routine_watcher, data))
		return (free_struct(data), 1);
	while (i < philo_nbr)
	{
		if (pthread_create(&temp->thread, NULL, routine, temp))
			return (free_struct(data), 2);
		temp = temp->next;
		i++;
	}
	i = 0;
	if (pthread_join(data->watcher, NULL))
		return (free_struct(data), 3);
	while (i < philo_nbr)
	{
		if (pthread_join(temp->thread, NULL))
			return (free_struct(data), 4);
		temp = temp->next;
		i++;
	}
	return (0);
}
