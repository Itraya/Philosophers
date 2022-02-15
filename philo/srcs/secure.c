/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:10:39 by mlagrang          #+#    #+#             */
/*   Updated: 2022/02/15 12:12:14 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	ft_print(t_philo *philo, char *txt)
{
	pthread_mutex_lock(&philo->gl->printm);
	if (philo->gl->print == 1)
		printf("%lld %d %s\n", get_time() - philo->gl->start, philo->id, txt);
	pthread_mutex_unlock(&philo->gl->printm);
}

void	ft_whilephi(t_philo *phi)
{
	while (1)
	{
		pthread_mutex_lock(&phi->gl->deathm);
		if (phi->gl->death != 0)
			break ;
		pthread_mutex_unlock(&phi->gl->deathm);
		ft_eat(phi);
		pthread_mutex_lock(&phi->gl->deathm);
		if (phi->gl->death != 0)
			break ;
		pthread_mutex_unlock(&phi->gl->deathm);
		ft_sleep(phi);
		ft_think(phi);
	}
	pthread_mutex_unlock(&phi->gl->deathm);
}

void	ft_whilemain(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo[i].ttodiem);
		if (philo[i].ttodie <= get_time())
		{
			pthread_mutex_unlock(&philo[i].ttodiem);
			break ;
		}
		pthread_mutex_unlock(&philo[i].ttodiem);
		pthread_mutex_lock(&philo[i].gl->nbpleinm);
		if (philo[i].gl->nbplein == philo[i].gnbphilo)
		{
			pthread_mutex_unlock(&philo[i].gl->nbpleinm);
			break ;
		}
		pthread_mutex_unlock(&philo[i].gl->nbpleinm);
		i++;
		if (i == philo[0].gnbphilo)
			i = 0;
	}
}

void	ft_death(t_gphilos *gb)
{
	pthread_mutex_lock(&gb->printm);
	pthread_mutex_lock(&gb->deathm);
	gb->death = 1;
	gb->print = 0;
	pthread_mutex_unlock(&gb->printm);
	pthread_mutex_unlock(&gb->deathm);
}
