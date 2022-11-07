/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:30:03 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/07 16:57:36 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

void	ft_eat(philo *p)
{
	t_data *d;

	d = (t_data*)p->data;
	printf("%ldms %d is eating\n", timestamp(d), p->name);
	ft_usleep(d->tteat, d);
	p->lunch_time = timestamp(d);
	pthread_mutex_lock(&p->lfork.mutex);
	p->lfork.isfree = 1;
	pthread_mutex_unlock(&p->lfork.mutex);
	p->forkinuse--;
	pthread_mutex_lock(&p->rfork->mutex);
	p->rfork->isfree = 1;
	pthread_mutex_unlock(&p->rfork->mutex);
	p->forkinuse--;
	p->nb_lumch++;
	if (timestamp(d) < (p->lunch_time + d->ttdie))
	{
		printf("%ldms %d is sleeping\n", timestamp(d), p->name);
		ft_usleep(d->ttsleep, d);
	}
	if (timestamp(d) < (p->lunch_time + d->ttdie))
		printf("%ldms %d is thinking\n", timestamp(d), p->name);
}

void	ft_take_forks(philo *p)
{
	t_data *d;

	d = (t_data*)p->data;

	pthread_mutex_lock(&p->lfork.mutex);
	if (p->lfork.isfree == 1)
	{
		p->lfork.isfree = 0;
		p->forkinuse++;
		printf("%ldms %d has taken a fork\n", timestamp(d), p->name);
	}
	pthread_mutex_unlock(&p->lfork.mutex);

	//Taking the right Fork
	pthread_mutex_lock(&p->rfork->mutex);
	if (p->rfork->isfree == 1)
	{
		p->rfork->isfree = 0;
		p->forkinuse++;
		printf("%ldms %d has taken a fork\n", timestamp(d), p->name);
	}
	pthread_mutex_unlock(&p->rfork->mutex);
}

void	*philos_function(void *data)
{
	philo		*p;
	t_data		*d;
	p = (philo *)data;
	d = (t_data *)p->data;

	if (p->name % 2)
		ft_usleep(1, d);
	p->nb_lumch = 0;
	while (p->nb_lumch != d->nb_must_eat && timestamp(d) < (p->lunch_time + d->ttdie))
	{
		//Tente de prendre les fourchettes
		ft_take_forks(p);
		//Se met a manger s'il a deux fourchettes.
		if (p->forkinuse == 2)
			ft_eat(p);
	}
	d->nbfullphilos++;
	return (NULL);
}


void	*control_function(void *data)
{
	int		i;
	t_data	*d;

	i = 0;
	d = (t_data*)data;
	while (d->nbfullphilos != d->nbphilos)
	{
		while (i < d->nbphilos)
		{
			if (timestamp(d) > (d->philosopher[i].lunch_time + d->ttdie))
			{
				printf("%ldms %d died\n", timestamp(d) ,d->philosopher[i].name);
				//system("leaks philo");
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
	data->nbfullphilos = 0;
	data->start_time = 0;
	data->start_time = timestamp(data);
	data->nbphilos = ft_atoi(argv[1]);
	data->philosopher = malloc(sizeof(philo) * data->nbphilos);
	data->ttdie = ft_atoi(argv[2]);
	data->tteat = ft_atoi(argv[3]);
	data->ttsleep = ft_atoi(argv[4]);
	data->nb_must_eat = -1;
	if (argc == 6)
		data->nb_must_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	int		i = 0;
	t_data	data;
	pthread_t supervisor;

	data_init(&data, argc, argv);
	if (data.nbphilos < 0)
		return(0);
	while (i < data.nbphilos)
	{
		data.philosopher[i].name = i + 1;
		data.philosopher[i].lfork.isfree = 1;
		pthread_mutex_init(&data.philosopher[i].lfork.mutex, NULL);
		if (i == 0)
			data.philosopher[i].rfork = &data.philosopher[data.nbphilos - 1].lfork;
		else
			data.philosopher[i].rfork = &data.philosopher[i - 1].lfork;
		data.philosopher[i].data = &data;
		data.philosopher[i].lunch_time = 0;
		pthread_create(&data.philosopher[i].thread, NULL, philos_function, &data.philosopher[i]);
		pthread_detach(data.philosopher[i].thread);
		i++;
	}
	pthread_create(&supervisor, NULL, control_function, &data);
	pthread_join(supervisor, NULL);

	//system("leaks philo");
	return (0);
}
