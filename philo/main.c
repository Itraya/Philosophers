/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 10:05:22 by mlagrang          #+#    #+#             */
/*   Updated: 2022/03/29 11:33:08 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int)1000) + (tv.tv_usec / 1000));
}

void	ft_msleep(int ms)
{
	int	time;
	int	i;

	time = get_time();
	i = time;
	while (i < time + ms)
	{
		i = get_time();
		usleep(100);
	}
}

t_philo	*ft_free(t_philo *philo, t_gphilos *gb, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_destroy(&philo[i].forkr);
		pthread_mutex_destroy(&philo[i].statusm);
		pthread_mutex_destroy(&philo[i].ttodiem);
		i++;
	}
	pthread_mutex_destroy(&gb->nbpleinm);
	pthread_mutex_destroy(&gb->deathm);
	pthread_mutex_destroy(&gb->printm);
	pthread_mutex_destroy(&gb->startm);
	free(philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_gphilos	gb;
	int			i;

	if (ac < 5 || ac > 6 || !ft_isnb(av))
		return (0 * printf("Mauvais arguments\n"));
	philo = ft_init(av, &gb);
	if (philo)
	{
		i = ft_whilemain(philo);
		ft_death(&gb);
		if (gb.nbplein != philo[0].gnbphilo)
			ft_print(&philo[i], "died");
		i = 0;
		while (i < philo[i].gnbphilo - 1)
		{
			pthread_mutex_lock(&philo[i].statusm);
			if (philo[i].status == 0)
				i++;
			pthread_mutex_unlock(&philo[i].statusm);
		}
	}
	usleep(100000);
	if (philo)
		ft_free(philo, &gb, philo[0].gnbphilo);
}
