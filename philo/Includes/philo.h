/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:51:36 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/14 14:21:06 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//LIBRARIES
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

//DEFINES
# define DEAD 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define INIT 4
# define DFLAG 5
# define FFLAG 6

//STRUCTURES
typedef struct s_philo
{
	int				id;
	pthread_mutex_t	meals_eaten_mutex;
	int				meals_eaten;
	int				philo_number;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_to_eat;
	int				*dead_flag;
	int				*full_flag;
	pthread_mutex_t	mutex_last_meal;
	size_t			time_last_meal;
	pthread_t		thread;
	pthread_mutex_t	fork;
	size_t			current_time;
	pthread_mutex_t	state_mutex;
	int				state;
	struct s_data	*data;
	struct s_philo	*next;
	struct s_philo	*prev;
}			t_philo;

typedef struct s_error
{
	size_t			type;
	struct s_error	*next;
}			t_error;

typedef struct s_data
{
	int				philo_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	pthread_mutex_t	dflag;
	int				dead_flag;
	pthread_mutex_t	fflag;
	int				full_flag;
	size_t			starttime;
	pthread_mutex_t	print;
	pthread_t		watcher;
	t_philo			*philos;
	t_error			*errors;
}			t_data;

//PROTOTYPES
void	init_struct(t_data *data, char **argv);
int		arg_has_wrong_char(char *str);
int		add_error(t_error **error_lst, size_t error);
void	display_errors(t_error *errors);
int		ft_atoi(const char *str);
void	ft_usleep(size_t to_sleep);
size_t	get_time_ms(void);
void	philo_init(t_data *data);
void	free_struct(t_data *data);
void	threads_init(t_data *data, t_philo *lst, int philo_nbr);
int		end_condition(t_philo *philo);
void	*routine_watcher(void *arg);
void	*routine(void *arg);
void	print(char *to_display, t_philo *philo);
int		end_condition(t_philo *philo);

#endif
