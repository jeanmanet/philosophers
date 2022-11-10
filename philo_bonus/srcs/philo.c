/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:30:03 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/10 18:47:53 by jmanet           ###   ########.fr       */
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
	sem_post(d->forks);
	p->forkinuse--;
	sem_post(d->forks);
	p->forkinuse--;
	p->nb_lumch++;
	printf("%ldms %d is sleeping\n", timestamp(d), p->name);
	ft_usleep(d->ttsleep, p);
	printf("%ldms %d is thinking\n", timestamp(d), p->name);
}

void	ft_take_forks(t_philo *p)
{
	t_data	*d;

	d = p->data;
	sem_wait(d->forks);
		p->forkinuse++;
		printf("%ldms %d has taken a fork\n", timestamp(d), p->name);
	if (d->nbphilos != 1)
	{
	sem_wait(d->forks);
		p->forkinuse++;
		printf("%ldms %d has taken a fork\n", timestamp(d), p->name);
	}
}

void	philos_function(t_philo *p)
{
	t_data	*d;

	d = (t_data *)p->data;
	p->nb_lumch = 0;
	p->lunch_time = 0;
	if (p->name % 2)
		ft_usleep(5, p);
	while (p->nb_lumch != d->nb_must_eat)
	{
		if (p->forkinuse != 2)
		{
			if (d->nbphilos == 1 && p->forkinuse == 1)
				ft_usleep(1, p);
			else
				ft_take_forks(p);
		}
		else
			ft_eat(p);
		ft_usleep(1, p);
	}
	ft_exit(d);
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
	data->philosopher = malloc(sizeof(t_philo) * data->nbphilos);
	data->ttdie = ft_atoi(argv[2]);
	data->tteat = ft_atoi(argv[3]);
	data->ttsleep = ft_atoi(argv[4]);
	data->nb_must_eat = -1;
	if (argc == 6)
		data->nb_must_eat = ft_atoi(argv[5]);
	data->semname = "fork20";
}

int	main(int argc, char **argv)
{
	int		i;
	int		ret;
	t_data	d;

	i = 0;
	data_init(&d, argc, argv);
	d.forks = sem_open(d.semname, O_CREAT, 0777, d.nbphilos);
	while (i < d.nbphilos)
	{
		d.philosopher[i].pid = fork();
		if (d.philosopher[i].pid == 0)
		{
			d.philosopher[i].name = i + 1;
			d.philosopher[i].data = &d;
		philos_function(&d.philosopher[i]);
		}
		i++;
	}
	ft_waitprocessus(&d);
	ft_exit(&d);
	return (0);
}
