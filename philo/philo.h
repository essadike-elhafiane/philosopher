/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelhafia <eelhafia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 23:04:30 by eelhafia          #+#    #+#             */
/*   Updated: 2023/03/30 20:33:15 by eelhafia         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	mutex_time;
	pthread_mutex_t	*print;
	pthread_t		pth;
	long int		num_philo;
	long int		die;
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

t_data_philo	*init_data(char **av, int ac, pthread_mutex_t	*print);
int				ft_check_error(char **spl);
long			ft_atoi(const char *str);
int				sup_max_int(t_data_philo *data);
long int		time_die(void);
void			ft_usleep(long int time_in_ms);
void			init_lst(int ac, char **av, t_data_philo *data,
					pthread_mutex_t *print);
void			ft_free(t_data_philo *data);
void			destroy(t_data_philo *data, pthread_mutex_t	*print);
int				is_died(t_data_philo *data, pthread_mutex_t	*print, int i);
#endif
