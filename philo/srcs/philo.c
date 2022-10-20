/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:30:03 by jmanet            #+#    #+#             */
/*   Updated: 2022/10/19 13:16:59 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

int	timestamp(t_data *data)
{
	struct timeval tv;
	long timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec/1000);

	return(timestamp - data->start_time);
}

void	*routine_function(void *data)
{
	philo		*p;
	t_data		*d;
	p = (philo *)data;
	d = (t_data *)p->data;
	//d = (t_data *)data;

	//pthread_mutex_init(&d->mutex, NULL);
	//count = &d->count;
	//thread = pthread_self();

	while (1)
	{
		pthread_mutex_lock(p->mutex);
		if (p->lfork == 1 && *p->rfork == 1)
		{
			p->lfork = 0;
			printf("%dms %d has taken a fork\n", timestamp(d), p->name);
			*p->rfork = 0;
			printf("%dms %d has taken a fork\n", timestamp(d), p->name);
			pthread_mutex_unlock(p->mutex);
			printf("%dms %d start to eat\n", timestamp(d), p->name);
			usleep(p->tteat * 1000);
			p->lunch_time = timestamp(d);
			pthread_mutex_lock(p->mutex);
			p->lfork = 1;
			*p->rfork = 1;
			pthread_mutex_unlock(p->mutex);
		}
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
		data.philosopher[i].lfork = 1;
		if (i == 0)
			data.philosopher[i].rfork = &data.philosopher[data.nbphilos - 1].lfork;
		else
			data.philosopher[i].rfork = &data.philosopher[i - 1].lfork;
		data.philosopher[i].ttdie = ft_atoi(argv[2]);
		data.philosopher[i].tteat = ft_atoi(argv[3]);
		data.philosopher[i].ttsleep = ft_atoi(argv[4]);
		data.philosopher[i].mutex = &data.mutex;
		data.philosopher[i].data = &data;
		data.philosopher[i].lunch_time = 0;
		pthread_create(&data.philosopher[i].thread, NULL, routine_function, &data.philosopher[i]);
		i++;
	}

	pthread_create(&supervisor, NULL, control_function, &data);



	pthread_join(data.philosopher->thread, NULL);
	// pthread_join(thread2, NULL);


	return (0);

}
