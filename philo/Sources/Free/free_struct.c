/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:36:30 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/21 14:26:15 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo *lst, int philo_nbr)
{
	t_philo	*temp;
	int		i;

	i = 0;
	temp = lst;
	while (i < philo_nbr)
	{
		temp = lst;
		lst = lst->next;
		free(temp);
		i++;
	}
	lst = NULL;
}

void	free_struct(t_data *data)
{
	if (data->philos)
		free_philos(data->philos, data->philo_number);
}
