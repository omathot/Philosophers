/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:29:28 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/02 22:06:46 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	are_letters(char *str, int mode)
{
	int	i;
	int	value;

	i = 0;
	while (str[i])
	{
		value = ft_atoi(str);
		if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
			return (1);
		if (mode == 0)
		{
			if (value == 0)
				return (1);
		}
		if (mode == 1)
			return (0);
		i++;
	}
	return (0);
}

void	check_input(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("wrong number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if (ft_atoi(argv[1]) > 200)
	{
		printf("200 philosophers maximum\n");
		exit(EXIT_FAILURE);
	}
	while (argv[i])
	{
		if (i == 5 && argv[5])
		{
			if (are_letters(argv[i], 1) == 1)
			{
				printf("found letters or incorect value, should only be numbers in input, only last input can be 0\n");
				exit(EXIT_FAILURE);
			}
			else
				return ;
		}
		else
		{
			if (are_letters(argv[i], 0) == 1)
			{
				printf("found letters or incorect value, should only be numbers in input, only last input can be 0\n");
				exit(EXIT_FAILURE);
			}
		}
		i++;
	}
}

/*
5 800 200 200 7
5 — The number of philosophers
800 — The time a philosopher will die if he doesn’t eat
200 — The time it takes a philosopher to eat
200 — The time it takes a philosopher to sleep
7 — Number of times all the philosophers need to eat before terminating the program **
*/
int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philo[200];
	pthread_mutex_t	forks[200];

	check_input(argc, argv);
	initializations(philo, forks, &program, argv);
	create_threads(&program, forks);
	free_all(&program, forks);
	return (0);
}
