/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 23:04:24 by eelhafia          #+#    #+#             */
/*   Updated: 2023/04/06 19:50:13 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routin_help_2(t_data_philo *da)
{
	da->num_eat++;
	pthread_mutex_unlock(&da->mutex_time);
	pthread_mutex_unlock(&da->mutex_fork);
	pthread_mutex_unlock(&da->next->mutex_fork);
	pthread_mutex_lock(da->print);
	if (da->die == 1)
	{
		pthread_mutex_unlock(da->print);
		return (1);
	}
	printf("%ld philo %ld is sleeping\n",
		time_die() - da->time_entre, da->num_philo);
	pthread_mutex_unlock(da->print);
	ft_usleep(da->time_sleep);
	pthread_mutex_lock(da->print);
	if (da->die == 1)
	{
		pthread_mutex_unlock(da->print);
		return (1);
	}
	printf("%ld philo %ld is thinking\n",
		time_die() - da->time_entre, da->num_philo);
	pthread_mutex_unlock(da->print);
	return (0);
}

int	routin_help_1(t_data_philo *da)
{
	pthread_mutex_lock(&da->next->mutex_fork);
	pthread_mutex_lock(da->print);
	if (da->die == 1)
	{
		pthread_mutex_unlock(da->print);
		return (1);
	}
	printf("%ld philo  %ld take a fork \n",
		time_die() - da->time_entre, da->num_philo);
	pthread_mutex_unlock(da->print);
	pthread_mutex_lock(da->print);
	if (da->die == 1)
	{
		pthread_mutex_unlock(da->print);
		return (1);
	}
	printf("%ld philo  %ld is eating\n",
		time_die() - da->time_entre, da->num_philo);
	pthread_mutex_unlock(da->print);
	pthread_mutex_lock(&da->mutex_time);
	da->time = time_die();
	pthread_mutex_unlock(&da->mutex_time);
	ft_usleep(da->time_eat);
	pthread_mutex_lock(&da->mutex_time);
	return (0);
}

void	*routin(void *data)
{
	t_data_philo	*da;

	da = data;
	if (da->num_philo % 2 == 0)
		ft_usleep(da->time_eat / 2);
	while (1)
	{
		if (da->max_eat == da->num_eat)
			return (NULL);
		pthread_mutex_lock(&da->mutex_fork);
		pthread_mutex_lock(da->print);
		if (da->die == 1)
		{
			pthread_mutex_unlock(da->print);
			return (NULL);
		}
		printf("%ld philo %ld take a fork \n",
			time_die() - da->time_entre, da->num_philo);
		pthread_mutex_unlock(da->print);
		if (routin_help_1(da))
			return (NULL);
		if (routin_help_2(da))
			return (NULL);
	}
	return (NULL);
}

int	init_pthread(t_data_philo	*data, int i)
{
	i = 1;
	while (i <= data->max_num_ph)
	{
		if (pthread_mutex_init(&data->mutex_fork, NULL))
			return (1);
		if (pthread_mutex_init(&data->mutex_time, NULL))
			return (1);
		if (pthread_create(&data->pth, NULL, routin, data))
			return (1);
		data = data->next;
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data_philo	*data;
	pthread_mutex_t	print;
	int				i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (write(1, "Error arg !\n", 12), 1);
	if (ft_check_error(av))
		return (write(1, "Error not number or num negative \n", 35), 1);
	pthread_mutex_init(&print, NULL);
	data = init_data(av, ac, &print);
	if (sup_max_int(data))
		return (free(data), write(1, "Error arg > max_int \n", 22), 1);
	if (data->max_num_ph == 0 || data->max_eat == 0
		|| data->time_die == 0 || data->time_sleep == 0 || data->max_eat == 0)
		return (free(data), write(1, "Error NULL arg!\n", 16), 1);
	init_lst(ac, av, data, &print);
	if (init_pthread(data, i))
		return (ft_free(data), write(1, "Error in phtread \n", 19), 1);
	if (is_died(data, &print, i))
		return (ft_free(data), 0);
}
