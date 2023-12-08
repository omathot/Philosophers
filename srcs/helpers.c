/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:56:41 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/06 15:37:19 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		printf("philo[%i]->id = %i\n", i, philo[i].id);
		printf("philo[%i]->eating = %i\n", i, philo[i].eating);
		printf("philo[%i]->meals_eaten = %i\n", i, philo[i].meals_eaten);
		printf("philo[%i]->time_to_die = %zu\n", i, philo[i].time_to_die);
		printf("philo[%i]->time_to_eat = %zu\n", i, philo[i].time_to_eat);
		printf("philo[%i]->time_to_sleep = %zu\n", i, philo[i].time_to_sleep);
		printf("philo[%i]->num_of_times_to_eat = %d\n", i,
			philo[i].num_times_to_eat);
		printf("philo[%i]->start_time = %lld\n", i, philo[i].start_time);
		printf("philo[%i]->last_meal = %zu\n", i, philo[i].last_meal);
		printf("philo[%i]->write_lock = %p\n", i, philo[i].write_lock);
		printf("philo[%i]->dead_lock = %p\n", i, philo[i].dead_lock);
		printf("philo[%i]->meal_lock = %p\n", i, philo[i].meal_lock);
		printf("philo[%i]->dead = %p\n", i, philo[i].dead);
		printf("philo[%i]->l_fork = %p\n", i, philo[i].l_fork);
		printf("philo[%i]->r_fork = %p\n", i, philo[i].r_fork);
		i++;
	}
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->dead == 1)
		{
			pthread_mutex_unlock(philo->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(philo->dead_lock);
		usleep(300);
	}
	return (0);
}

int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (write(2, "gettimeofday() error\n", 22), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	free_all(t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	while (i < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	print_message(char *str, t_philo *philo, int id)
{
	int	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead(philo))
		printf("[%d] philo[%d] %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}
