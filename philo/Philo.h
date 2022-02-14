/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 10:05:54 by mlagrang          #+#    #+#             */
/*   Updated: 2022/02/14 16:30:16 by mlagrang         ###   ########.fr       */
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
	int				ttodie;
	int				ttoeat;
	int				ttosleep;
	int				nbtoeat;
	int				nbphilo;
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

#endif