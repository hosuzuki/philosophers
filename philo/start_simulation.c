/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/05 17:19:10 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_all_mutex(t_lst *l, long num_philo)
{
	long	i;

	pthread_mutex_destroy(&(l->mt->mt_end_flag));
	pthread_mutex_destroy(&(l->mt->mt_write));
	i = 0;
	while (i < num_philo)
		pthread_mutex_destroy(&(l->mt->mt_forks[i++]));
}

void	*life_of_philo(void *arg) 
{
	t_lst	*l;
	long	time_eat;
	long	time_think;

	l = (t_lst *)arg;
	if (l->index % 2)
		usleep (200);
	if ((time_eat = what_time()) < 0)
		return (NULL);
	while (1)
	{
		if ((time_eat = eat_task(l, time_eat)) < 0)
			return (NULL);
		if (sleep_task(l, time_eat) < 0)
			return (NULL);
		if ((time_think = what_time()) < 0)
			return (NULL);
		put_status(l, time_think, THINKING);
	}
	return (NULL);
}

int	start_simulation(t_lst *l, long num_philo)
{
	long	i;
	pthread_t *philos;

	philos = (pthread_t *)malloc(sizeof(pthread_t) * num_philo);
	if (!philos)
		return (free_all(l->info, l->mt, l));
	i = 0;
	while (i < num_philo)
	{
		pthread_create(&philos[i], NULL, life_of_philo, &l[i]);
		i++;
	}
	i = 0;
	while (i < num_philo)
		pthread_join(philos[i++], NULL);
	destroy_all_mutex(l, num_philo);
	return(0);
}
