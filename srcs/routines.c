/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:34:13 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/01 23:33:12 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sleepy(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead(philo))
		printf("[%lld], philo[%d] is sleeping\n", time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	ft_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead(philo))
		printf("[%lld], philo[%d] is thinking\n", time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	eating(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(philo->r_fork);
	time = get_current_time();
	printf("[%lld], philo[%d] has taken a fork\n", time, philo->id);

	pthread_mutex_lock(philo->l_fork);
	time = get_current_time();
	printf("[%lld], philo[%d] has taken a fork\n", time, philo->id);

	philo->eating = 1;
	time = get_current_time();
	printf("[%lld], philo[%d] is eating\n", time, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
