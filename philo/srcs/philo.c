/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:30:03 by jmanet            #+#    #+#             */
/*   Updated: 2022/10/20 16:25:18 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

long	timestamp(t_data *data)
{
	struct timeval tv;
	long timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec/1000);

	return(timestamp - data->start_time);
}

void	ft_usleep(long time)
{
	long	start_time;

	start_time = init_ms();
	while (init_ms() - start_time < time)
		usleep(time * 10);
}

void	*philos_function(void *data)
{
	philo		*p;
	t_data		*d;
	p = (philo *)data;
	d = (t_data *)p->data;

	if (p->name % 2)
		usleep(1000);
	while (1)
	{
		//Tente de prendre les fourchettes seulement s'il a vraiment faim
	//	if ((p->ttdie - p->ttsleep) / (2 + p->name) < timestamp(p->data) - p->lunch_time)
		{
			pthread_mutex_lock(&p->lfork.mutex);
			if (p->lfork.isfree == 1)
			{
				p->lfork.isfree = 0;
				p->forkinuse++;
				printf("%dms %d has taken a fork\n", timestamp(d), p->name);
			}
			pthread_mutex_unlock(&p->lfork.mutex);

			//Taking the right Fork
			pthread_mutex_lock(&p->rfork->mutex);
			if (p->rfork->isfree == 1)
			{
				p->rfork->isfree = 0;
				p->forkinuse++;
				printf("%dms %d has taken a fork\n", timestamp(d), p->name);
			}
			pthread_mutex_unlock(&p->rfork->mutex);
		}

		//Se met a manger si il a deux fourchettes.
		if (p->forkinuse == 2)
		{
			printf("%dms %d is eating\n", timestamp(d), p->name);
			p->lunch_time = timestamp(d);
			usleep(p->tteat * 1000);
			p->lunch_time = timestamp(d);
		//Repose ses fourchettes
			pthread_mutex_lock(&p->lfork.mutex);
			p->lfork.isfree = 1;
			pthread_mutex_unlock(&p->lfork.mutex);
			p->forkinuse--;
			pthread_mutex_lock(&p->rfork->mutex);
			p->rfork->isfree = 1;
			pthread_mutex_unlock(&p->rfork->mutex);
			p->forkinuse--;
		//Et se met a dormir
			printf("%dms %d is sleeping\n", timestamp(d), p->name);
			usleep(p->ttsleep * 1000);
		//Se reveille et se met a penser
			printf("%dms %d is thinking\n", timestamp(d), p->name);
		}
		/*
			pthread_mutex_unlock(p->rmutex);

			p->lunch_time = timestamp(d);
			pthread_mutex_lock(&p->mutex);
			pthread_mutex_lock(p->rmutex);
			p->lfork = 1;
			*p->rfork = 1;
			pthread_mutex_unlock(&p->mutex);
			pthread_mutex_unlock(p->rmutex);
		*/
	}

	return (NULL);
}

void	*control_function(void *data)
{
	int		i;
	t_data	*d;

	i = 0;
	d = (t_data*)data;
	while (1)
	{
		while (i < d->nbphilos)
		{
			if (timestamp(d) > (d->philosopher[i].lunch_time + d->philosopher->ttdie))
			{
				printf("%dms %d died\n", timestamp(d) ,d->philosopher[i].name);
				exit(0);
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}


void	data_init(t_data *data, int argc, char **argv)
{
	(void)argc;
	data->count = 0;
	data->start_time = 0;
	data->start_time = timestamp(data);
	data->nbphilos = ft_atoi(argv[1]);
	data->philosopher = malloc(sizeof(philo) * data->nbphilos);
}

int	main(int argc, char **argv)
{
	int		i = 0;
	t_data	data;
	pthread_t supervisor;

	data_init(&data, argc, argv);
	while (i < data.nbphilos)
	{
		data.philosopher[i].name = i + 1;
		data.philosopher[i].lfork.isfree = 1;
		if (i == 0)
		{
			data.philosopher[i].rfork = &data.philosopher[data.nbphilos - 1].lfork;
		}
		else
		{
			data.philosopher[i].rfork = &data.philosopher[i - 1].lfork;
		}
		data.philosopher[i].ttdie = ft_atoi(argv[2]);
		data.philosopher[i].tteat = ft_atoi(argv[3]);
		data.philosopher[i].ttsleep = ft_atoi(argv[4]);
		data.philosopher[i].data = &data;
		data.philosopher[i].lunch_time = 0;
		data.philosopher[i].forkinuse = 0;
		pthread_create(&data.philosopher[i].thread, NULL, philos_function, &data.philosopher[i]);
		i++;
	}

	pthread_create(&supervisor, NULL, control_function, &data);



	pthread_join(data.philosopher->thread, NULL);
	// pthread_join(thread2, NULL);


	return (0);

}
