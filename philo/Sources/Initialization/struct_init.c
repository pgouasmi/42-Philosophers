/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:13:19 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/07 13:36:39 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	parse_argv(t_data *data, char **argv)
{
	size_t	j;

	j = 1;
	data->errors = NULL;
	data->arg_error = 0;
	while (argv[j])
	{
		if (arg_has_wrong_char(argv[j]))
		{
			data->arg_error++;
			if (add_error(&data->errors, j))
				return (free_struct(data), exit(2));
		}
		j++;
	}
}

static void	argv_into_struct(t_data	*data, char **argv)
{
	parse_argv(data, argv);
	if (data->arg_error)
		return (display_errors(data->errors), free_struct(data), exit(2));
	data->philo_number = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atoi(argv[5]);
}

__uint64_t	get_time_ms(void)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL))
		return (0);
	return ((time_value.tv_sec * 1000) + (time_value.tv_usec / 1000));
}

void test_usleep()
{
	__uint64_t time;
	__uint64_t request;
	__uint64_t actual;

	request = 1000000;
	time = get_time_ms();
	usleep(request);
	actual = (get_time_ms() - time);
	printf("actual = %ld\n", actual);
}

void	*routine(void *arg)
{
	t_data *temp;

	temp = (t_data *)arg;
	while (temp->philo_number <1000)
		temp->philo_number++;
	return (NULL);
}

void	test_thread(void)
{
	t_data *data;
	pthread_t t1;
	pthread_t t2;

	data = malloc(sizeof(*data));
	data->philo_number = 0;
	pthread_create(&t1, NULL, routine, data);
	pthread_create(&t2, NULL, routine, data);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("after threads, phi_num = %d", data->philo_number);

}

void	init_struct(t_data *data, char **argv)
{
	argv_into_struct(data, argv);
	data->starttime = get_time_ms();
	printf("time day = %ld\n", data->starttime);
	test_usleep();
	test_thread();
}
