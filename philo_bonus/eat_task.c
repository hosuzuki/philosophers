/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_task.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 23:54:35 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	pickup_forks(t_lst *l)
{
	long	time;

	sem_wait(l->sem->forks);
	sem_wait(l->sem->writer);
	printf("%ld %ld has taken a fork\n", what_time(), l->index);
	sem_post(l->sem->writer);
	sem_wait(l->sem->forks);
	sem_wait(l->sem->writer);
//	printf("forks3:%ld\n", l->index);
	time = what_time();
	sem_wait(l->meal_flag);
	l->last_meal = time;
	sem_post(l->meal_flag);
	printf("%ld %ld is eating\n", time, l->index);
	sem_post(l->sem->writer);
	activate_death_watcher(l);
	return (time);
}

long	eat_task(t_lst *l)
{
	long	time;

	time = pickup_forks(l);
	while (!task_is_finished(time, l->info->ms_eat))
		usleep(INTERVAL);
	sem_post(l->sem->forks);
	sem_post(l->sem->forks);
	if (l->info->num_to_eat != -1)
	{
		l->info->num_to_eat--;
		if (l->info->num_to_eat == 0)
			exit(0);
	}
	return (0);
}
