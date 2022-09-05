/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_task.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/05 22:18:19 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*static void	lock_forks(t_lst *l, long index, long num_philo)
{
	pthread_mutex_lock(&(l->mt->mt_forks[index - 1]));
	pthread_mutex_lock(&(l->mt->mt_fork[index % num_philo]));
}

static void	unlock_forks(t_lst *l, long index, long num_philo)
{
	pthread_mutex_unlock(&(l->mt->mt_forks[index - 1]));
	pthread_mutex_unlock(&(l->mt->mt_fork[index % num_philo]));
}
*/

static int	pickup_forks(t_lst *l, long index, long num_philo)
{
	long	time_one_fork;

//	lock_forks(l, i, lst->n_philo);
	if (l->status == THINKING) 
	{
		pthread_mutex_lock(&(l->mt->mt_forks[index - 1]));
		time_one_fork = what_time();
		put_status(l, time_one_fork, ONE_FORK);
		pthread_mutex_unlock(&(l->mt->mt_forks[index - 1]));
		return (1);
	}
	else if (l->status == ONE_FORK)
	{
		pthread_mutex_lock(&(l->mt->mt_forks[index % num_philo]));
		l->last_meal = what_time();
		put_status(l, l->last_meal, EATING);
		pthread_mutex_unlock(&(l->mt->mt_forks[index % num_philo]));
		return (0);
	}
//	unlock_forks(l, i, lst->n_philo);
	return (0);
}

long	eat_task(t_lst *l, long time_eat)
{
	while (pickup_forks(l, l->index, l->info->num_philo))
	{
		if (is_end(l, time_eat))
			return (-1);
		usleep(INTERVAL);
	}
//	if ((time_eat = what_time()) < 0)
//		return (-1);
//	put_status(lst->index, time_eat, EATING);
	while (!task_is_finished(l->last_meal, l->info->ms_eat))
	{
		if (is_end(l, l->last_meal))
			return (-1);
		usleep(INTERVAL);
	}
//	if (finish_eating(l))
//		return (-1);
	return (0);
}
