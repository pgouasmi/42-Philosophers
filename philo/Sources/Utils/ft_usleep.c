/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:13:43 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/14 14:14:16 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t to_sleep)
{
	size_t	value;

	value = get_time_ms();
	while (get_time_ms() - value < to_sleep)
	{
		usleep(100);
	}
}
