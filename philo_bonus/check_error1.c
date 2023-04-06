/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:03:41 by eelhafia          #+#    #+#             */
/*   Updated: 2023/04/03 01:22:01 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data_philo *data)
{
	int				i;
	t_data_philo	*tmp;

	i = data->max_num_ph;
	tmp = data;
	while (i > 1)
	{
		if (tmp->num_philo == i)
		{
			free(tmp);
			tmp = data;
			i--;
		}
		tmp = tmp->next;
	}
	free(data);
}

void	ft_wait(t_data_philo *data)
{
	int	i;

	i = 0;
	while (++i < data->max_num_ph)
	{
		wait(NULL);
		data = data->next;
	}
}

void	init_lst(int ac, char **av, t_data_philo *data)
{
	int				i;
	t_data_philo	*tmp;

	i = 1;
	data->num_philo = i++;
	tmp = data;
	while (i <= data->max_num_ph)
	{
		tmp->next = init_data(av, ac);
		tmp = tmp->next;
		tmp->num_philo = i++;
	}
	tmp->next = data;
}

void	check_is_died(t_data_philo *da)
{
	if (time_die() - da->time >= da->time_die)
	{
		sem_wait(da->sem_time);
		usleep(10);
		printf("%ld philo %ld is died\n",
			time_die() - da->time_entre, da->num_philo);
		exit(1);
	}
}
