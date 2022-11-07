/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:30:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/07 16:16:23 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct d_data
{
	pthread_mutex_t	mutex;
	int				isfree;
}	pfork;

typedef struct p_data
{
	pthread_t	thread;
	pfork		lfork;
	pfork		*rfork;
	int			name;
	int			forkinuse;
	int			lunch_time;
	int			nb_lumch;

	void		*data;
}	philo;

typedef struct s_data
{
	long	start_time;
	int		nbphilos;
	int		nbfullphilos;
	int			ttdie;
	int			tteat;
	int			ttsleep;
	int 		nb_must_eat;

	philo	*philosopher;
}	t_data;

int		ft_atoi(const char *nptr);
long	timestamp(t_data *data);
void	ft_usleep(long time, t_data *data);

#endif

