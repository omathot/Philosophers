/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:47:57 by omathot           #+#    #+#             */
/*   Updated: 2023/12/08 14:48:09 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	if (48 <= c && c <= 57)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void	look_non_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (!(ft_isdigit(argv[i][j])))
			{
				printf("Invalid input\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}
