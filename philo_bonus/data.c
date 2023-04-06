/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:30:21 by eelhafia          #+#    #+#             */
/*   Updated: 2023/04/03 01:20:12 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data_help(t_data_philo *data)
{
	static sem_t	*b;
	static sem_t	*timee;
	static sem_t	*mutex;
	static int		k;

	sem_unlink("sem_fork");
	sem_unlink("sem_time");
	sem_unlink("mutex");
	if (k == 0)
	{
		b = sem_open("sem_fork", O_CREAT | O_EXCL, S_IRWXU, data->max_num_ph);
		timee = sem_open("sem_time", O_CREAT | O_EXCL, S_IRWXU, 1);
		mutex = sem_open("mutex", O_CREAT, S_IRUSR | S_IWUSR, 1);
		k++;
	}
	data->sem_mutex = mutex;
	data->sem_fork = b;
	data->sem_time = timee;
}

t_data_philo	*init_data(char **av, int ac)
{
	t_data_philo	*data;

	data = malloc(sizeof(t_data_philo));
	data->num_eat = 0;
	data->time = 0;
	data->max_num_ph = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_eat = ft_atoi(av[5]);
	else
		data->max_eat = -1;
	init_data_help(data);
	data->next = NULL;
	return (data);
}

int	sup_max_int(t_data_philo *data)
{
	if (data->max_eat > 2147483647)
		return (1);
	if (data->max_num_ph > 2147483647)
		return (1);
	if (data->time_die > 2147483647)
		return (1);
	if (data->time_eat > 2147483647)
		return (1);
	if (data->time_sleep > 2147483647)
		return (1);
	return (0);
}

long int	time_die(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

int	ft_usleep(long int time_in_ms, t_data_philo *data)
{
	long int	start_time;

	start_time = 0;
	start_time = time_die();
	while ((time_die() - start_time) < time_in_ms)
	{
		if (time_die() - data->time >= data->time_die)
		{
			sem_wait(data->sem_time);
			printf("%ld philo %ld is died\n",
				time_die() - data->time_entre, data->num_philo);
			exit(1);
		}
		usleep(100);
	}
	return (0);
}
