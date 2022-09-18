/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/18 23:17:05 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
char *test(t_lst *l, char *s)
{
	printf("index: %ld - Status: %s\n", l->index, s);
	return (NULL);
}
*/

void	*life_of_philo(void *arg)
{
	t_lst	*l;
	long	time_think;

	l = (t_lst *)arg;
	if (l->index % 2)
		usleep (2500);
	pthread_mutex_lock(l->philo);
	l->last_meal = what_time();
	if (l->last_meal < 0)
	{
		pthread_mutex_unlock(l->philo);
		return (NULL);
	}
	pthread_mutex_unlock(l->philo);
	activate_death_watcher(l);
	while (1)
	{
		if (eat_task(l) < 0)
			return (NULL);
			//return (test(l, "eat"));// delete this later.
		if (sleep_task(l) < 0)
			return (NULL);
			//return (test(l, "sleep"));
		time_think = what_time();
		if (time_think < 0)
			return (NULL);
		if (put_status(l, time_think, THINKING) < 0)
			return (NULL);
			//return (test(l, "think"));
	}
	return (NULL);
}

int	start_simulation(t_data *data, t_lst *lst, long num_philo)
{
	long		i;
	pthread_t	*threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * num_philo);
	if (!philos)
		return (free_all(l->info, l->share, data, l));
	i = 0;
	while (i < num_philo)
	{
		pthread_create(&threads[i], NULL, life_of_philo, &l[i]);
		i++;
	}
	i = 0;
	while (i < num_philo)
		pthread_join(threads[i++], NULL);
	destroy_all_mutex(data, num_philo);
	free (threads);
	return (0);
}
