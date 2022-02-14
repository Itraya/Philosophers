/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 10:05:22 by mlagrang          #+#    #+#             */
/*   Updated: 2022/02/14 16:33:48 by mlagrang         ###   ########.fr       */
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

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->forkl);
	//HAS TAKEN A FORK
	pthread_mutex_lock(&philo->forkr);
	//HAS TAKEN A FORK
	philo->nbeat++;
	pthread_mutex_lock(&philo->gl->nbpleinm);
	if (philo->nbeat == philo->gl->nbtoeat)
		philo->gl->nbplein++;
	pthread_mutex_unlock(&philo->gl->nbpleinm);
	pthread_mutex_lock(&philo->gl->printm);
	if (philo->gl->print == 1)
		printf("%lld %d is eating\n", get_time() - philo->gl->start, philo->id);
	pthread_mutex_unlock(&philo->gl->printm);
	ft_msleep(philo->gl->ttoeat);
	pthread_mutex_lock(&philo->ttodiem);
	philo->ttodie = get_time() + (get_time() - philo->gl->ttodie);
	pthread_mutex_unlock(&philo->ttodiem);
	pthread_mutex_unlock(philo->forkl);
	pthread_mutex_unlock(&philo->forkr);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->gl->printm);
	if (philo->gl->print == 1)
		printf("%lld %d is sleeping\n", get_time() - philo->gl->start, philo->id);
	pthread_mutex_unlock(&philo->gl->printm);
	ft_msleep(philo->gl->ttosleep);
}

void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->gl->printm);
	if (philo->gl->print == 1)
		printf("%lld %d is thinking\n", get_time() - philo->gl->start, philo->id);
	pthread_mutex_unlock(&philo->gl->printm);
}

void	*ft_philo(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	pthread_mutex_lock(&phi->gl->startm);
	pthread_mutex_unlock(&phi->gl->startm);
	pthread_mutex_lock(&phi->ttodiem);
	phi->ttodie = get_time() + phi->gl->ttodie;
	pthread_mutex_unlock(&phi->ttodiem);
	//printf("%d\n", phi->id);
	while (1)
	{
		pthread_mutex_lock(&phi->gl->deathm);
		if (phi->gl->death != 0)
			break ;
		pthread_mutex_unlock(&phi->gl->deathm);
		ft_eat(phi);
		ft_sleep(phi);
		ft_think(phi);
	}
	pthread_mutex_unlock(&phi->gl->deathm);
	pthread_mutex_lock(&phi->statusm);
	phi->status = 0;
	pthread_mutex_unlock(&phi->statusm);
	//printf("%d mor\n", phi->id);
	return (philo);
}

t_philo	*ft_prep(char **av, t_gphilos *gb)
{
	t_philo			*philo;
	int				i;

	gb->nbphilo = ft_atoi(av[1]);
	gb->ttodie = ft_atoi(av[2]);
	gb->ttoeat = ft_atoi(av[3]);
	gb->ttosleep = ft_atoi(av[4]);
	if (av[5])
		gb->nbtoeat = ft_atoi(av[5]);
	philo = malloc(sizeof(t_philo) * gb->nbphilo);
	i = -1;
	while (++i < gb->nbphilo)
	{
		philo[i].id = i + 1;
		philo[i].gl = gb;
		philo[i].status = 1;
		philo[i].ttodie = get_time() + philo[i].gl->ttodie;
		pthread_mutex_init(&philo[i].forkr, NULL);
		pthread_mutex_init(&philo[i].statusm, NULL);
		pthread_mutex_init(&philo[i].ttodiem, NULL);
		if (i > 0)
			philo[i].forkl = &philo[i - 1].forkr;
	}
	if (i > 0)
		philo[0].forkl = &philo[i - 1].forkr;
	return (philo);
}

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

void	ft_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->gl->nbphilo)
	{
		if (pthread_create(&philo->thread, NULL, ft_philo, (void *)&philo[i]))
			printf("Error\n");
		pthread_detach(philo->thread);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_gphilos	gb;
	int			i;
	int			j;

	if (ac < 5 || ac > 6 || !ft_isnb(av))
		return (0 * printf("Mauvais arguments\n"));
	philo = ft_prep(av, &gb);
	gb.print = 1;
	gb.death = 0;
	gb.nbplein = 0;
	pthread_mutex_init(&gb.printm, NULL);
	pthread_mutex_init(&gb.deathm, NULL);
	pthread_mutex_init(&gb.startm, NULL);
	pthread_mutex_init(&gb.nbpleinm, NULL);
	pthread_mutex_lock(&gb.startm);
	ft_thread(philo);
	usleep(100);
	gb.start = get_time();
	pthread_mutex_unlock(&gb.startm);
	i = 0;
	j = 0;
	while (1)
	{
		pthread_mutex_lock(&philo[i].ttodiem);
		if (philo[i].ttodie <= get_time())
			break ;
		pthread_mutex_unlock(&philo[i].ttodiem);
		if (i == philo[i].gl->nbphilo - 1)
			i = 0;
		pthread_mutex_lock(&philo[i].gl->nbpleinm);
		if (philo[i].gl->nbplein == philo[i].gl->nbphilo)
			break ;
		pthread_mutex_unlock(&philo[i].gl->nbpleinm);
		if (j == gb.nbphilo)
			break ;
	}
	pthread_mutex_unlock(&philo[i].ttodiem);
	//printf("a\n");
	pthread_mutex_lock(&gb.printm);
	pthread_mutex_lock(&gb.deathm);
	philo[i].gl->death = 1;
	gb.print = 0;
	pthread_mutex_unlock(&gb.printm);
	pthread_mutex_unlock(&gb.deathm);
	if (philo[i].gl->nbplein != philo[i].gl->nbphilo)
		printf("%lld %d is ded\n", get_time() - philo->gl->start, philo->id);
	i = 0;
	while (i < philo[i].gl->nbphilo - 1)
	{
		pthread_mutex_lock(&philo[i].statusm);
		if (philo[i].status == 0)
			i++;
		pthread_mutex_unlock(&philo[i].statusm);
	}
	usleep(100000);
	free(philo);
}
