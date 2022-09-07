/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_dev.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/06 15:36:11 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_all_mutex(t_lst *l, long num_philo)
{
	long	i;

	pthread_mutex_destroy(&(l->mt->mt_end_flag));
//	if (l->mt->end_flag == OVER_EAT_COUNT)
		pthread_mutex_destroy(&(l->mt->mt_write));
	i = 0;
	while (i < num_philo)
		pthread_mutex_destroy(&(l->mt->mt_forks[i++]));
}

void	*life_of_philo(void *arg) 
{
	t_lst	*l;
//	long	time_eat;
	long	time_think;

	l = (t_lst *)arg;
	if (l->index % 2)
		usleep (200);
	if ((l->last_meal = what_time()) < 0)
		return (NULL);
//	long i = 0;
	while (1)
	{
	//	if ((time_eat = eat_task(l, l_last_meal)) < 0)
		if (eat_task(l, l->last_meal) < 0)
			return (NULL);
		if (sleep_task(l, l->last_meal) < 0)
			return (NULL);
		if ((time_think = what_time()) < 0)
			return (NULL);
		if (put_status(l, time_think, THINKING) < 0)
			return (NULL);
//		if (i++ >= l->info->num_philo)
//			return (NULL) ;
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
	life_of_philo(&l[i]);
	destroy_all_mutex(l, num_philo);
	free (philos); //is this necessary?
	return(0);
}
