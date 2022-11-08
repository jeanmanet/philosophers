/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:30:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/08 16:58:23 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct t_fork
{
	pthread_mutex_t	mutex;
	int				isfree;
}	t_fork;

typedef struct t_philo
{
	pthread_t	thread;
	t_fork		lfork;
	t_fork		*rfork;
	int			name;
	int			forkinuse;
	int			lunch_time;
	int			nb_lumch;

	void		*data;
}	t_philo;

typedef struct s_data
{
	long	start_time;
	int		nbphilos;
	int		fullphilos;
	int		ttdie;
	int		tteat;
	int		ttsleep;
	int		nb_must_eat;
	t_philo	*philosopher;
}	t_data;

int		ft_atoi(const char *nptr);
long	timestamp(t_data *data);
void	ft_usleep(long time, t_philo *p);
void	ft_exit(t_data *data);
void	ft_exit_error_thread(t_data *d);

#endif
