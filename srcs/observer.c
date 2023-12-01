/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:49:49 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/01 22:22:50 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_died(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= philo->time_to_die && philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_death(t_philo *philo)
{
	int	i;
	int	time;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		if (philo_died(philo) == 1)
		{
			time = get_current_time();
			printf("%d %d died\n", time, philo[i].id);
			pthread_mutex_lock(philo[0].dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
	}
	return (0);
}

int	full(t_philo *philo)
{
	int	i;
	int	ate;

	i = 0;
	ate = 0;
	if (philo->num_times_to_eat == -1)
		return (0);
	while (i < philo->num_of_philos)
	{
		pthread_mutex_lock(philo->meal_lock);
		if (philo->meals_eaten >= philo->num_times_to_eat)
			ate++;
		pthread_mutex_unlock(philo->meal_lock);
		i++;
	}
	if (ate == philo->num_of_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*observe(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		if (check_death(philo) == 1 || full(philo) == 1)
			break ;
	}
	return (pointer);
}