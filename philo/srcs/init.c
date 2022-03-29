/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:22:14 by mlagrang          #+#    #+#             */
/*   Updated: 2022/02/17 15:16:13 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	ft_prepwhile(t_philo *philo, int i, t_gphilos *gb)
{
	philo[i].id = i + 1;
	philo[i].gl = gb;
	philo[i].status = 1;
	philo[i].ttodie = get_time() + philo[i].gttodie;
	philo[i].nbeat = 0;
	pthread_mutex_init(&philo[i].forkr, NULL);
	pthread_mutex_init(&philo[i].statusm, NULL);
	pthread_mutex_init(&philo[i].ttodiem, NULL);
	if (i > 0)
		philo[i].forkl = &philo[i - 1].forkr;
}

t_philo	*ft_prep(char **av, t_gphilos *gb)
{
	t_philo			*philo;
	int				i;

	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		philo[i].gnbphilo = ft_atoi(av[1]);
		philo[i].gttodie = ft_atoi(av[2]);
		philo[i].gttoeat = ft_atoi(av[3]);
		philo[i].gttosleep = ft_atoi(av[4]);
		if (av[5])
			philo[i].gnbtoeat = ft_atoi(av[5]);
		ft_prepwhile(philo, i, gb);
	}
	if (i > 0)
		philo[0].forkl = &philo[i - 1].forkr;
	gb->print = 1;
	gb->death = 0;
	gb->nbplein = 0;
	pthread_mutex_init(&gb->printm, NULL);
	pthread_mutex_init(&gb->deathm, NULL);
	pthread_mutex_init(&gb->startm, NULL);
	pthread_mutex_init(&gb->nbpleinm, NULL);
	return (philo);
}

t_philo	*ft_init(char **av, t_gphilos *gb)
{
	t_philo	*philo;

	philo = ft_prep(av, gb);
	if (!philo)
		return (0);
	pthread_mutex_lock(&gb->startm);
	if (!ft_thread(philo))
		return (ft_free(philo, philo->gl, philo->gnbphilo));
	usleep(1000);
	gb->start = get_time();
	pthread_mutex_unlock(&gb->startm);
	return (philo);
}
