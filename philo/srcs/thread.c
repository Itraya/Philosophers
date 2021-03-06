/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:10:58 by mlagrang          #+#    #+#             */
/*   Updated: 2022/03/29 11:49:06 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	*ft_philo(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	pthread_mutex_lock(&phi->gl->startm);
	pthread_mutex_unlock(&phi->gl->startm);
	pthread_mutex_lock(&phi->ttodiem);
	phi->ttodie = get_time() + phi->gttodie;
	pthread_mutex_unlock(&phi->ttodiem);
	if (phi->id % 2 == 0)
	{
		ft_think(phi);
		ft_msleep(phi->gttoeat - 1);
	}
	ft_whilephi(phi);
	pthread_mutex_lock(&phi->statusm);
	phi->status = 0;
	pthread_mutex_unlock(&phi->statusm);
	return (philo);
}

int	ft_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->gnbphilo)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_philo, (void *)&philo[i]))
		{
			printf("Error\n");
			pthread_mutex_lock(&philo[i].gl->printm);
			pthread_mutex_lock(&philo[i].gl->deathm);
			philo[i].gl->death = 1;
			philo[i].gl->print = 0;
			pthread_mutex_unlock(&philo[i].gl->printm);
			pthread_mutex_unlock(&philo[i].gl->deathm);
			return (0);
		}
		pthread_detach(philo[i].thread);
		i++;
	}
	return (1);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->forkl);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->forkr);
	ft_print(philo, "has taken a fork");
	philo->nbeat++;
	ft_print(philo, "is eating");
	ft_msleep(philo->gttoeat);
	if (philo->nbeat == philo->gnbtoeat)
	{
		pthread_mutex_lock(&philo->gl->nbpleinm);
		philo->gl->nbplein++;
		pthread_mutex_unlock(&philo->gl->nbpleinm);
	}
	pthread_mutex_lock(&philo->ttodiem);
	philo->ttodie = get_time() + philo->gttodie;
	pthread_mutex_unlock(&philo->ttodiem);
	pthread_mutex_unlock(philo->forkl);
	pthread_mutex_unlock(&philo->forkr);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_msleep(philo->gttosleep);
}

void	ft_think(t_philo *philo)
{
	ft_print(philo, "is thinking");
}
