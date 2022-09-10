/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_task.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/10 18:17:16 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pickup_left_fork(t_lst *l, long index, long num_philo)
{
	long	time_one_fork;

	(void)num_philo;
	pthread_mutex_lock(&(l->mt->mt_forks[index - 1]));
	time_one_fork = what_time();
	if (put_status(l, time_one_fork, ONE_FORK) < 0)
	{
//		pthread_mutex_unlock(&(l->mt->mt_forks[index % num_philo]));
		return (1);
	}
//	pthread_mutex_unlock(&(l->mt->mt_forks[index - 1]));
	return (0);
}

static int	pickup_right_fork(t_lst *l, long index, long num_philo)
{
	if (l->info->num_philo == 1)
		return (1);
	pthread_mutex_lock(&(l->mt->mt_forks[index % num_philo]));
	l->last_meal = what_time();
	if (put_status(l, l->last_meal, EATING) < 0)
		return (1);
	return (0);
}

long	eat_task(t_lst *l, long last_meal)
{
	while (pickup_left_fork(l, l->index, l->info->num_philo))
	{
		if (is_end(l, last_meal))
			return (-1);
		usleep(INTERVAL);
	}
//	usleep(INTERVAL);
	while (pickup_right_fork(l, l->index, l->info->num_philo))
	{
		if (is_end(l, last_meal))
			return (-1);
		usleep(INTERVAL);
	}
//	usleep(INTERVAL);
	while (!task_is_finished(l->last_meal, l->info->ms_eat))
	{
		if (is_end(l, l->last_meal))
			return (-1);
		usleep(INTERVAL);
	}
	pthread_mutex_unlock(&(l->mt->mt_forks[l->index - 1]));
	pthread_mutex_unlock(&(l->mt->mt_forks[l->index % l->info->num_philo]));
//	usleep(INTERVAL);
	return (0);
}
