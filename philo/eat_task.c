/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_task.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 16:59:42 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pickup_left_fork(t_lst *l)
{
	pthread_mutex_lock(l->left_fork);
	if (put_status(l, what_time(), ONE_FORK) < 0)
	{
		pthread_mutex_unlock(l->left_fork);
		return (-1);
	}
	return (0);
}

static int	pickup_right_fork(t_lst *l)
{
	if (l->info->num_philo == 1)
	{
		while (!is_end(l))
			usleep (INTERVAL);
		pthread_mutex_unlock(l->left_fork);
		return (-1);
	}
	pthread_mutex_lock(l->right_fork);
	pthread_mutex_lock(l->philo);
	l->last_meal = what_time();
	if (put_status(l, l->last_meal, EATING) < 0)
	{
		pthread_mutex_unlock(l->philo);
		pthread_mutex_unlock(l->left_fork);
		pthread_mutex_unlock(l->right_fork);
		return (-1);
	}
	pthread_mutex_unlock(l->philo);
	return (0);
}

long	eat_task(t_lst *l)
{
	long	last_meal;

	if (pickup_left_fork(l) < 0)
		return (-1);
	if (pickup_right_fork(l) < 0)
		return (-1);
	pthread_mutex_lock(l->philo);
	last_meal = l->last_meal;
	pthread_mutex_unlock(l->philo);
	while (!task_is_finished(last_meal, l->info->ms_eat))
	{
		if (is_end(l))
		{
			pthread_mutex_unlock(l->left_fork);
			pthread_mutex_unlock(l->right_fork);
			return (-1);
		}
		usleep(INTERVAL);
	}
	pthread_mutex_unlock(l->left_fork);
	pthread_mutex_unlock(l->right_fork);
	return (0);
}
