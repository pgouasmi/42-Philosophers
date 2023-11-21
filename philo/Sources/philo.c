/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:49:18 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/21 14:15:35 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error\nWrong number of arguments\n", 32);
		return (1);
	}
	if (init_struct(&data, argv))
		return (1);
	threads_init(&data, data.philos, data.philo_number);
	return (free_struct(&data), 0);
}
