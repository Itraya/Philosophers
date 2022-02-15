/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 10:05:22 by mlagrang          #+#    #+#             */
/*   Updated: 2022/02/15 11:12:17 by mlagrang         ###   ########.fr       */
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
		usleep(10);
	}
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_gphilos	gb;
	int			i;

	if (ac < 5 || ac > 6 || !ft_isnb(av))
		return (0 * printf("Mauvais arguments\n"));
	philo = ft_init(av, &gb);
	ft_whilemain(philo);
	ft_death(&gb);
	if (gb.nbplein != philo[0].gnbphilo)
		printf("%lld %d died\n", get_time() - philo->gl->start, philo->id);
	i = 0;
	while (i < philo[i].gnbphilo - 1)
	{
		pthread_mutex_lock(&philo[i].statusm);
		if (philo[i].status == 0)
			i++;
		pthread_mutex_unlock(&philo[i].statusm);
	}
	usleep(100000);
	free(philo);
}
