/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:56:41 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/01 15:20:21 by oscarmathot      ###   ########.fr       */
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
		printf("philo[%i]->num_of_times_to_eat = %d\n", i, philo[i].num_times_to_eat);
		printf("philo[%i]->start_time = %zu\n", i, philo[i].start_time);
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