/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:13:19 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/21 14:10:56 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_argv(char **argv)
{
	size_t	j;

	j = 1;
	while (argv[j])
	{
		if (arg_has_wrong_char(argv[j]))
			return (display_errors((int)j), 1);
		j++;
	}
	return (0);
}

int	handle_meals_to_eat(t_data *data, char *str)
{
	data->meals_to_eat = ft_atoi(str);
	if (data->meals_to_eat > INTMAX || !data->meals_to_eat)
		return (display_errors(5), 5);
	return (0);
}

static int	argv_into_struct(t_data	*data, char **argv)
{
	if (parse_argv(argv))
		return (1);
	data->philo_number = ft_atoi(argv[1]);
	if (data->philo_number > INTMAX || !data->philo_number)
		return (display_errors(1), 1);
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die > INTMAX || !data->time_to_die)
		return (display_errors(2), 2);
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat > INTMAX || !data->time_to_eat)
		return (display_errors(3), 3);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep > INTMAX || !data->time_to_sleep)
		return (display_errors(4), 4);
	if (argv[5])
	{
		if (handle_meals_to_eat(data, argv[5]))
			return (1);
	}
	else
		data->meals_to_eat = -1;
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
	data->dead_flag = 0;
	data->full_flag = 0;
	if (argv_into_struct(data, argv))
		return (1);
	if (philo_init(data))
		return (2);
	data->starttime = get_time_ms();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->fflag, NULL);
	pthread_mutex_init(&data->dflag, NULL);
	return (0);
}
