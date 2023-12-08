/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:34:13 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/08 11:53:12 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sleepy(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	if (ft_usleep(philo->time_to_sleep, philo) == 1)
		return ;
}

void	thinking(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	died_while_wait(t_philo *philo)
{
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_sleep, philo);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	if (ft_usleep(philo->time_to_eat, philo) == 1)
	{
		died_while_wait(philo);
		return ;
	}
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
