/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:23:52 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 16:23:49 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_mutex(t_data *data, long num_philo)
{
	long	i;

	pthread_mutex_destroy(&(data->flag));
	pthread_mutex_destroy(&(data->writer));//
	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_destroy(&(data->philos[i]));
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	return ;
}

int	activate_mutex(t_data *data, long num_philo)
{
	long	i;

	errno = 0;
	pthread_mutex_init(&(data->flag), NULL);
	pthread_mutex_init(&(data->writer), NULL);
	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_init(&(data->philos[i]), NULL);
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
	if (errno != 0)
	{
		destroy_all_mutex(data, num_philo);
		return (-1);
	}
	return (0);
}
