/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:36:30 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/09 11:23:20 by pgouasmi         ###   ########.fr       */
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
}

void	free_lst(t_error *errors)
{
	t_error	*temp;

	while (errors)
	{
		temp = errors;
		errors = errors->next;
		free(temp);
	}
}

void	free_struct(t_data *data)
{
	if (data->errors)
		free_lst(data->errors);
	if (data->philos)
		free_philos(data->philos, data->philo_number);
}
