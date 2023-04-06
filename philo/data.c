/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:30:21 by eelhafia          #+#    #+#             */
/*   Updated: 2023/04/04 15:29:09 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data_philo	*init_data(char **av, int ac, pthread_mutex_t	*print)
{
	t_data_philo	*data;

	data = malloc(sizeof(t_data_philo));
	data->num_eat = 0;
	data->time = 0;
	data->die = 0;
	data->print = print;
	data->max_num_ph = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_eat = ft_atoi(av[5]);
	else
		data->max_eat = -1;
	data->next = NULL;
	return (data);
}

void	init_lst(int ac, char **av, t_data_philo *data, pthread_mutex_t *print)
{
	int				i;
	t_data_philo	*tmp;

	i = 1;
	data->num_philo = i++;
	tmp = data;
	while (i <= data->max_num_ph)
	{
		tmp->next = init_data(av, ac, print);
		tmp = tmp->next;
		tmp->num_philo = i++;
	}
	tmp->next = data;
	i = 1;
	while (i <= data->max_num_ph)
	{
		data->time_entre = time_die();
		data->time = data->time_entre;
		data = data->next;
		i++;
	}
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

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = time_die();
	while ((time_die() - start_time) < time_in_ms)
		usleep(200);
}
