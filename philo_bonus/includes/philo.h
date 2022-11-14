/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:30:39 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/14 12:46:16 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct p_data
{
	pid_t		pid;
	pthread_t	fthread;
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
	int		ttdie;
	int		tteat;
	int		ttsleep;
	int		nb_must_eat;
	t_philo	*philosopher;
	sem_t	*forks;
	char	*semname;
}	t_data;

int		ft_atoi(const char *nptr);
long	timestamp(t_data *data);
void	ft_usleep(long time, t_philo *p);
void	ft_exit(t_data *data);
void	ft_waitprocessus(t_data *data);
void	ft_exit_error(char *str);

#endif
