/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:13:19 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/20 15:13:50 by pgouasmi         ###   ########.fr       */
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

void	handle_meals_to_eat(t_data *data, char *str)
{
	data->meals_to_eat = ft_atoi(str);
	if (data->meals_to_eat > INTMAX || !data->meals_to_eat)
		add_error(&data->errors, 5);
}

static int	argv_into_struct(t_data	*data, char **argv)
{
	parse_argv(data, argv);
	if (data->errors)
		return (display_errors(data->errors), free_struct(data), 1);
	data->philo_number = ft_atoi(argv[1]);
	if (data->philo_number > INTMAX)
		add_error(&data->errors, 1);
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die > INTMAX)
		add_error(&data->errors, 2);
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat > INTMAX)
		add_error(&data->errors, 3);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep > INTMAX)
		add_error(&data->errors, 4);
	if (argv[5])
		handle_meals_to_eat(data, argv[5]);
	else
		data->meals_to_eat = -1;
	if (data->errors)
		return (display_errors(data->errors), free_struct(data), 1);
	return (0);
}

size_t	get_time_ms(void)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL))
		return (0);
	return ((time_value.tv_sec * 1000) + (time_value.tv_usec / 1000));
}

int	init_struct(t_data *data, char **argv)
{
	data->philos = NULL;
	data->errors = NULL;
	data->dead_flag = 0;
	data->full_flag = 0;
	if (argv_into_struct(data, argv))
		return (1);
	philo_init(data);
	data->starttime = get_time_ms();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->fflag, NULL);
	pthread_mutex_init(&data->dflag, NULL);
	return (0);
}
