/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:36:30 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/07 11:01:26 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
}
