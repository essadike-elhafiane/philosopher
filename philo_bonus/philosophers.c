/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 23:04:24 by eelhafia          #+#    #+#             */
/*   Updated: 2023/04/04 15:15:05 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routin_help(t_data_philo *da)
{
	if (da->time_eat * 2 >= da->time_die && da->num_philo % 2 == 0)
	{
		ft_usleep(da->time_die, da);
		sem_wait(da->sem_time);
		printf("%ld philo %ld is died\n",
			time_die() - da->time_entre, da->num_philo);
		exit(1);
	}
	sem_wait(da->sem_fork);
	check_is_died(da);
	sem_wait(da->sem_time);
	printf("%ld philo %ld take a fork \n",
		time_die() - da->time_entre, da->num_philo);
	printf("%ld philo %ld is eating\n",
		time_die() - da->time_entre, da->num_philo);
	sem_post(da->sem_time);
	da->time = time_die();
	ft_usleep(da->time_eat, da);
	sem_post(da->sem_fork);
	sem_post(da->sem_fork);
	da->num_eat++;
	sem_wait(da->sem_time);
	printf("%ld philo %ld is sleeping\n",
		time_die() - da->time_entre, da->num_philo);
	sem_post(da->sem_time);
}

void	*routin(void *data)
{
	t_data_philo	*da;

	da = data;
	da->time = time_die();
	if (da->num_philo % 2 == 0)
		ft_usleep(da->time_eat / 2, da);
	while (1)
	{
		if (da->num_eat == da->max_eat)
			exit(0);
		sem_wait(da->sem_fork);
		printf("%ld philo %ld take a fork \n",
			time_die() - da->time_entre, da->num_philo);
		if (da->max_num_ph == 1)
			exit(3);
		routin_help(da);
		ft_usleep(da->time_sleep, da);
		sem_wait(da->sem_time);
		printf("%ld philo %ld is thinking\n",
			time_die() - da->time_entre, da->num_philo);
		sem_post(da->sem_time);
	}
	return (NULL);
}

void	functions_wait(t_data_philo *data, int i)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status))
		{
			if (WEXITSTATUS(status) == 3)
			{
				ft_usleep(data->time_die, data);
				printf("%ld philo 1 is died\n", time_die() - data->time_entre);
				exit(0);
			}
			sem_close(data->sem_fork);
			sem_close(data->sem_time);
			while (++i <= data->max_num_ph)
			{
				kill(data->pid, SIGKILL);
				data = data->next;
			}
			exit(0);
		}
	}
	ft_wait(data);
}

int	init_time(t_data_philo	*data, int i)
{
	i = 1;
	while (i <= data->max_num_ph)
	{
		data->time_entre = time_die();
		data->time = data->time_entre;
		data = data->next;
		i++;
	}
	i = 1;
	while (i <= data->max_num_ph)
	{
		data->pid = fork();
		if (data->pid < 0)
			return (1);
		if (!data->pid)
			routin(data);
		data = data->next;
		i++;
	}
	i = 0;
	functions_wait(data, i);
	return (0);
}

int	main(int ac, char **av)
{
	t_data_philo	*data;
	int				i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (write(1, "Error arg !\n", 12), 0);
	if (ft_check_error(av))
		return (write(1, "Error not number or num negative \n", 35), 1);
	data = init_data(av, ac);
	if (sup_max_int(data))
		return (free(data), write(1, "Error arg > max_int \n", 22), 1);
	if (data->max_num_ph == 0 || data->max_eat == 0
		|| data->time_die == 0 || data->time_sleep == 0 || data->max_eat == 0)
		return (free(data), write(1, "Error NULL arg!\n", 16), 1);
	init_lst(ac, av, data);
	if (init_time(data, i))
		return (ft_free(data), write(1, "Error in fork \n", 16), 1);
}
