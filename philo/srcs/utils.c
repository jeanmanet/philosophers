/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:17:19 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/14 10:45:56 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	timestamp(t_data *data)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timestamp - data->start_time);
}

void	ft_usleep(long time, t_philo *p)
{
	long	start_time;
	t_data	*d;

	d = p->data;
	start_time = timestamp(d);
	while (timestamp(d) - start_time < time)
	{
		if (timestamp(d) >= (p->lunch_time + d->ttdie))
		{
			printf("%ldms %d died\n", timestamp(d), p->name);
			exit (0);
		}
		usleep(100);
	}
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbphilos)
	{
		pthread_exit(data->philosopher[i].thread);
		pthread_mutex_destroy(&data->philosopher[i].lfork.mutex);
		i++;
	}
	free(data->philosopher);
}

void	ft_exit_error_thread(t_data *d)
{
	printf("Error : Thread creation failed\n");
	ft_exit(d);
}

void	ft_exit_error(char *str)
{
	printf("Error : %s\n", str);
	exit (0);
}
