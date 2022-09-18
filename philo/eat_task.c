/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_task.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/18 23:18:11 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*death_handler(void *arg)
{
	t_lst	*l;
	long	tmp;

	l = (t_lst *)arg;
	tmp = l->last_meal;
	while (what_time() - l->last_meal <= l->info->ms_die)
	{
		if (tmp != l->last_meal)
			return (NULL);
		usleep(200);
	}
	pthread_mutex_lock(&(l->writer));
	if (is_end(l))
	{
		pthread_mutex_unlock(&(l->writer));
		return (NULL);
	}
	raise_end_flag(l, DEAD);
	printf("%ld %ld died\n", what_time(), l->index);
	pthread_mutex_unlock(&(l->writer));
	return (NULL);
}

void	activate_death_watcher(t_lst *l)
{
	pthread_t	tmp;

	pthread_create(&tmp, NULL, death_handler, l);
	pthread_detach(tmp);
}

static int	pickup_left_fork(t_lst *l, long index)
{
	long	time_one_fork;

	pthread_mutex_lock(&(l->mt->mt_forks[index - 1]));
	time_one_fork = what_time();
	if (time_one_fork < 0)
	{
		pthread_mutex_unlock(&(l->mt->mt_forks[l->index - 1]));
		return (-1);
	}
	if (put_status(l, time_one_fork, ONE_FORK) < 0)
	{
		pthread_mutex_unlock(&(l->mt->mt_forks[l->index - 1]));
		return (-1);
	}
	return (0);
}

static int	pickup_right_fork(t_lst *l, long index, long num_philo)
{
	if (l->info->num_philo == 1)
	{
		while (!is_end(l))
			usleep (INTERVAL);
		pthread_mutex_unlock(&(l->mt->mt_forks[l->index - 1]));
		return (-1);
	}
	pthread_mutex_lock(&(l->mt->mt_forks[index % num_philo]));
	l->last_meal = what_time();
	if (l->last_meal < 0 || put_status(l, l->last_meal, EATING) < 0)
	{
		pthread_mutex_unlock(&(l->mt->mt_forks[l->index - 1]));
		pthread_mutex_unlock(&(l->mt->mt_forks[l->index % l->info->num_philo]));
		return (-1);
	}
	return (0);
}

long	eat_task(t_lst *l)
{
	if (pickup_left_fork(l, l->index) < 0)
			return (-1);
	if (pickup_right_fork(l, l->index, l->info->num_philo) < 0)
		return (-1);
	while (!task_is_finished(l->last_meal, l->info->ms_eat))
	{
		if (is_end(l))
		{
			pthread_mutex_unlock(&(l->mt->mt_forks[l->index - 1]));
			pthread_mutex_unlock(&(l->mt->mt_forks[l->index % l->info->num_philo]));
			return (-1);
		}
		usleep(INTERVAL);
	}
	pthread_mutex_unlock(&(l->mt->mt_forks[l->index - 1]));
	pthread_mutex_unlock(&(l->mt->mt_forks[l->index % l->info->num_philo]));
	return (0);
}
