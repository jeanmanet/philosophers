/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:30:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/10/19 12:49:49 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct p_data
{
	pthread_t	thread;
	pthread_mutex_t *mutex;
	int			lunch_time;
	int		lfork;
	int		*rfork;
	int		name;
	int		ttdie;
	int		tteat;
	int		ttsleep;
	int 	tmeat;
	void	*data;
}	philo;

typedef struct s_data
{
	long	start_time;
	int		nbphilos;
	int		count;

	philo	*philosopher;
	pthread_mutex_t mutex;
}	t_data;

int	ft_atoi(const char *nptr);

#endif

