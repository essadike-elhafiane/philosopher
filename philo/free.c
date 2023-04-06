/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 22:53:35 by eelhafia          #+#    #+#             */
/*   Updated: 2023/04/01 00:50:24 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_died(t_data_philo *data, pthread_mutex_t	*print, int i)
{
	while (1)
	{
		ft_usleep(1);
		pthread_mutex_lock(&data->mutex_time);
		if (time_die() - data->time >= data->time_die)
		{
			pthread_mutex_lock(print);
			printf("%ld    philo %ld is died\n",
				time_die() - data->time_entre, data->num_philo);
			i = 0;
			while (++i <= data->max_num_ph)
			{
				data->die = 1;
				data = data->next;
			}
			pthread_mutex_unlock(print);
			pthread_mutex_unlock(&data->mutex_time);
			return (destroy(data, print), 1);
		}
		if (data->max_eat == data->num_eat)
			return (destroy(data, print), 1);
		pthread_mutex_unlock(&data->mutex_time);
		data = data->next;
	}
}

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

void	destroy(t_data_philo *data, pthread_mutex_t	*print)
{
	int	i;

	i = 0;
	while (++i <= data->max_num_ph && data->max_num_ph > 1)
	{
		pthread_join(data->pth, NULL);
		pthread_mutex_destroy(&data->mutex_fork);
		pthread_mutex_destroy(&data->mutex_time);
		data = data->next;
	}
	pthread_mutex_destroy(print);
}
