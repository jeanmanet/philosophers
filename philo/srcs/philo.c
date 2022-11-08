/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:30:03 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/08 16:31:07 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_eat(t_philo *p)
{
	t_data	*d;

	d = (t_data *)p->data;
	printf("%ldms %d is eating\n", timestamp(d), p->name);
	ft_usleep(d->tteat, p);
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
	if (p->nb_lumch == d->nb_must_eat)
		d->fullphilos++;
	printf("%ldms %d is sleeping\n", timestamp(d), p->name);
	ft_usleep(d->ttsleep, p);
	printf("%ldms %d is thinking\n", timestamp(d), p->name);
}

void	ft_take_forks(t_philo *p)
{
	t_data	*d;

	d = (t_data *)p->data;
	if (p->lfork.isfree == 1)
	{
		pthread_mutex_lock(&p->lfork.mutex);
		p->lfork.isfree = 0;
		pthread_mutex_unlock(&p->lfork.mutex);
		p->forkinuse++;
		printf("%ldms %d has taken a fork\n", timestamp(d), p->name);
	}
	if (p->rfork->isfree == 1)
	{
		pthread_mutex_lock(&p->rfork->mutex);
		p->rfork->isfree = 0;
		pthread_mutex_unlock(&p->rfork->mutex);
		p->forkinuse++;
		printf("%ldms %d has taken a fork\n", timestamp(d), p->name);
	}
}

void	*philos_function(void *data)
{
	t_philo		*p;
	t_data		*d;

	p = (t_philo *)data;
	d = (t_data *)p->data;
	pthread_mutex_init(&p->lfork.mutex, NULL);
	p->lfork.isfree = 1;
	p->nb_lumch = 0;
	p->lunch_time = 0;
	if (p->name % 2)
		ft_usleep(1, p);
	while (p->nb_lumch != d->nb_must_eat)
	{
		ft_take_forks(p);
		if (p->forkinuse == 2)
			ft_eat(p);
		ft_usleep(1, p);
	}
	while (d->fullphilos != d->nbphilos)
		ft_usleep(1, p);
	return (NULL);
}

void	data_init(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error : Incorrect number of arguments\n");
		exit (0);
	}
	data->start_time = 0;
	data->start_time = timestamp(data);
	data->nbphilos = ft_atoi(argv[1]);
	if (data->nbphilos < 1)
	{
		printf("Error : There must be at leat one philosopher !\n");
		exit(0);
	}
	data->fullphilos = 0;
	data->philosopher = malloc(sizeof(t_philo) * data->nbphilos);
	data->ttdie = ft_atoi(argv[2]);
	data->tteat = ft_atoi(argv[3]);
	data->ttsleep = ft_atoi(argv[4]);
	data->nb_must_eat = -1;
	if (argc == 6)
		data->nb_must_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	int		i;
	int		ret;
	t_data	d;

	i = 0;
	data_init(&d, argc, argv);
	while (i < d.nbphilos)
	{
		d.philosopher[i].name = i + 1;
		if (i == 0)
			d.philosopher[i].rfork = &d.philosopher[d.nbphilos - 1].lfork;
		else
			d.philosopher[i].rfork = &d.philosopher[i - 1].lfork;
		d.philosopher[i].data = &d;
		ret = pthread_create(&d.philosopher[i].thread, NULL, philos_function,
				&d.philosopher[i]);
		if (ret != 0)
			ft_exit_error_thread(&d);
		i++;
	}
	while (i-- <= 0)
		pthread_join(d.philosopher[i].thread, NULL);
	ft_exit(&d);
	return (0);
}
