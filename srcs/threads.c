/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:46:27 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/01 22:11:08 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead(philo))
	{
		eating(philo);
		sleepy(philo);
		thinking(philo);
	}
	return (pointer);
}

void	create_threads(t_program *program)			// , pthread_mutex_t *forks
{
	pthread_t	observer;
	int			i;

	i = 0;
	pthread_create(&observer, NULL, &observe, program->philos);
	while (i < program->philos[0].num_of_philos)
	{
		pthread_create(&program->philos[i].thread, NULL, &routine, &program->philos[i]);
		i++;
	}
	pthread_join(observer, NULL);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
}
