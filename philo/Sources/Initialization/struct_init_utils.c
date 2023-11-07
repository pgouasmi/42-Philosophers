/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:28:39 by pgouasmi          #+#    #+#             */
/*   Updated: 2023/11/07 11:32:08 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_errors(t_error *errors)
{
	t_error	*temp;

	temp = errors;
	while (temp)
	{
		if (errors->type == 1)
			printf("Bad input : `Number_of_philosophers'\n");
		else if (errors->type == 2)
			printf("Bad input : `Time_to_die'\n");
		else if (errors->type == 3)
			printf("Bad input : `Time_to_eat'\n");
		else if (errors->type == 4)
			printf("Bad input : `Time_to_sleep'\n");
		else
			printf("Bad input : `Number_of_times_each_philosopher_must_eat'\n");
		temp = temp->next;
	}
}

int	add_error(t_error **error_lst, size_t error)
{
	t_error	*new;
	t_error	*temp;

	new = malloc(sizeof(*new));
	if (!new)
		return (1);
	new->type = error;
	if (!*error_lst)
		*error_lst = new;
	else
	{
		temp = *error_lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	new->next = NULL;
	return (0);
}

static int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	arg_has_wrong_char(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!is_num(str[i]))
			return (1);
		i++;
	}
	return (0);
}
