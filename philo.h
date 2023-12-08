/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:29:44 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/06 15:00:08 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long long		start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_program;

int			get_current_time(void);
void		initializations(t_philo *philo,
				pthread_mutex_t *forks, t_program *program, char **argv);
int			create_threads(t_program *program, pthread_mutex_t *forks);
void		print_philos(t_philo *philo);
void		sleepy(t_philo *philo);
void		thinking(t_philo *philo);
void		eating(t_philo *philo);
int			ft_usleep(size_t milliseconds, t_philo *philo);
int			dead(t_philo *philo);
void		*observe(void *pointer);
void		free_all(t_program *program, pthread_mutex_t *forks);
void		print_message(char *str, t_philo *philo, int id);
int			ft_atoi(const char *str);

#endif
