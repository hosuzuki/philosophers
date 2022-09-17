/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/16 19:45:40 by hos              ###   ########.fr       */
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
	l->last_meal = what_time();
	if (l->last_meal < 0)
		return (NULL);
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

int	start_simulation(t_lst *l, long num_philo)
{
	long		i;
	pthread_t	*philos;

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
	free (philos);
	return (0);
}
