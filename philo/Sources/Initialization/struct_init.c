/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:13:19 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/09 15:56:30 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	parse_argv(t_data *data, char **argv)
{
	size_t	j;

	j = 1;
	while (argv[j])
	{
		if (arg_has_wrong_char(argv[j]))
		{
			if (add_error(&data->errors, j))
				return (free_struct(data), exit(2));
		}
		j++;
	}
}

static void	argv_into_struct(t_data	*data, char **argv)
{
	parse_argv(data, argv);
	if (data->errors)
		return (display_errors(data->errors), free_struct(data), exit(2));
	data->philo_number = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atoi(argv[5]);
	else
		data->meals_to_eat = -1;
}

size_t	get_time_ms(void)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL))
		return (0);
	return ((time_value.tv_sec * 1000) + (time_value.tv_usec / 1000));
}

void	init_struct(t_data *data, char **argv)
{
	data->philos = NULL;
	data->errors = NULL;
	data->dead_flag = 0;
	argv_into_struct(data, argv);
	philo_init(data);
	data->starttime = get_time_ms();
	// printf("time day = %ld\n", data->starttime);
}
