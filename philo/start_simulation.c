/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 16:58:04 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life_of_philo(void *arg)
{
	t_lst	*l;

	l = (t_lst *)arg;
	if (l->index % 2)
		usleep (200);
	pthread_mutex_lock(l->philo);
	l->last_meal = what_time();
	pthread_mutex_unlock(l->philo);
	activate_death_watcher(l);
	while (1)
	{
		if (eat_task(l) < 0)
			return (NULL);
		if (sleep_task(l) < 0)
			return (NULL);
		if (put_status(l, what_time(), THINKING) < 0)
			return (NULL);
	}
	return (NULL);
}

int	start_simulation(t_data *data, t_lst *l, long num_philo)
{
	long		i;
	pthread_t	*threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * num_philo);
	if (!threads)
		return (free_all(l->info, l->flags, data, l));
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
