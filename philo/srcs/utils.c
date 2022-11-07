/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:17:19 by jmanet            #+#    #+#             */
/*   Updated: 2022/11/07 16:56:54 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		nb = (nb * 10) + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}

long	timestamp(t_data *data)
{
	struct timeval tv;
	long timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec/1000);

	return(timestamp - data->start_time);
}

void	ft_usleep(long time, t_data *data)
{
	long	start_time;

	start_time = timestamp(data);
	while (timestamp(data) - start_time < time)
		usleep(time * 10);
}
