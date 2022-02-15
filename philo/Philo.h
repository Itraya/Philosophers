/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 10:05:54 by mlagrang          #+#    #+#             */
/*   Updated: 2022/02/15 11:12:56 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_gphilos
{
	int				nbplein;
	pthread_mutex_t	nbpleinm;
	pthread_mutex_t	deathm;
	pthread_mutex_t	printm;
	int				death;
	int				print;
	int64_t			start;
	pthread_mutex_t	startm;
}				t_gphilos;

typedef struct s_philo
{
	int				gttodie;
	int				gttoeat;
	int				gttosleep;
	int				gnbtoeat;
	int				gnbphilo;
	int				id;
	int				status;
	pthread_mutex_t	statusm;
	int				nbeat;
	int64_t			ttodie;
	pthread_mutex_t	ttodiem;
	pthread_mutex_t	*forkl;
	pthread_mutex_t	forkr;
	t_gphilos		*gl;
	pthread_t		thread;
}				t_philo;

void	ft_print(t_philo *philo, char *txt);
void	ft_whilephi(t_philo *phi);
void	ft_whilemain(t_philo *philo);
int		ft_isnb(char **av);
int		ft_atoi(char *a);
t_philo	*ft_prep(char **av, t_gphilos *gb);
void	ft_prepwhile(t_philo *philo, int i, t_gphilos *gb);
int64_t	get_time(void);
void	ft_msleep(int ms);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
t_philo	*ft_init(char **av, t_gphilos *gb);
void	ft_death(t_gphilos *gb);
void	*ft_philo(void *philo);
void	ft_thread(t_philo *philo);

#endif