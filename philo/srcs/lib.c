/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:21:16 by mlagrang          #+#    #+#             */
/*   Updated: 2022/02/15 12:12:11 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

int	ft_isnb(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9' || ft_atoi(av[i]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *a)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (a[i])
	{
		nb = (a[i] - '0') + nb * 10;
		i++;
	}
	return (nb);
}
