/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 23:04:30 by eelhafia          #+#    #+#             */
/*   Updated: 2023/04/03 01:22:19 by eelhafia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include  <string.h>
# include <sys/types.h>
# include <signal.h>
# include <semaphore.h>
# include <dispatch/dispatch.h>

typedef struct s_philo
{
	sem_t			*sem_fork;
	sem_t			*sem_time;
	sem_t			*sem_mutex;
	pid_t			pid;
	pthread_t		pth;
	pthread_mutex_t	mutex_time;
	long int		num_philo;
	long int		num_eat;
	long int		time_sleep;
	long int		time_die;
	long int		time_entre;
	long int		time_eat;
	long int		max_num_ph;
	long int		time;
	long int		max_eat;
	struct s_philo	*next;
}	t_data_philo;

t_data_philo	*init_data(char **av, int ac);
int				ft_check_error(char **spl);
long			ft_atoi(const char *str);
int				sup_max_int(t_data_philo *data);
long int		time_die(void);
void			check_is_died(t_data_philo *da);
int				ft_usleep(long int time_in_ms, t_data_philo *data);
void			ft_free(t_data_philo *data);
void			ft_wait(t_data_philo *data);
void			init_lst(int ac, char **av, t_data_philo *data);
#endif
