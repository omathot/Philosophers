/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:22:06 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/01 22:13:56 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_input(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_of_philos = ft_atoi(argv[1]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	initialize_program_n_forks(t_philo *philo, t_program *program, char **argv, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	program->dead_flag = 0;
	program->philos = philo;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	initializations(t_philo *philo, pthread_mutex_t *forks, t_program *program, char **argv)
{
	int	i;

	i = 0;
	initialize_program_n_forks(philo, program, argv, forks);
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		init_input(&philo[i], argv);
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		philo[i].write_lock = &program->write_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].dead = &program->dead_flag;
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[philo[i].num_of_philos - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
	// print_philos(philo);
}
