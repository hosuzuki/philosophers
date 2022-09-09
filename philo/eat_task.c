/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_task.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/09 15:05:44 by hos              ###   ########.fr       */
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

static int	pickup_left_fork(t_lst *l, long index, long num_philo)
{
	long	time_one_fork;

//	lock_forks(l, i, lst->n_philo);
//	if (l->status == THINKING) 
//	{
		pthread_mutex_lock(&(l->mt->mt_forks[index - 1]));
		time_one_fork = what_time();
		if (put_status(l, time_one_fork, ONE_FORK) < 0)
		{
			pthread_mutex_unlock(&(l->mt->mt_forks[index % num_philo]));
			return (1);
		}
		pthread_mutex_unlock(&(l->mt->mt_forks[index - 1]));
//		return (1);
//	}
//	unlock_forks(l, i, lst->n_philo);
	return (0);
}

static int	pickup_right_fork(t_lst *l, long index, long num_philo)
{
	//long	eat_time;

//	else if (l->status == ONE_FORK)
//	{
		if (l->info->num_philo == 1)
			return (1);
		pthread_mutex_lock(&(l->mt->mt_forks[index % num_philo]));
		l->last_meal = what_time();
		if (put_status(l, l->last_meal, EATING) < 0)
		{
			pthread_mutex_unlock(&(l->mt->mt_forks[index % num_philo]));
			return (1);
		}
		pthread_mutex_unlock(&(l->mt->mt_forks[index % num_philo]));
		return (0);
//	}
//	unlock_forks(l, i, lst->n_philo);
//	return (0);
}
long	eat_task(t_lst *l, long last_meal)
{
	while (pickup_left_fork(l, l->index, l->info->num_philo))
	{
//		printf("in pickup left\n");
		if (is_end(l, last_meal))
			return (-1);
		usleep(INTERVAL);
	}
	usleep(INTERVAL);
	//printf("out pickup left\n");
	while (pickup_right_fork(l, l->index, l->info->num_philo))
	{
	//	printf("in pickup right\n");
		if (is_end(l, last_meal))
			return (-1);
		usleep(INTERVAL);
	}//	if ((time_eat = what_time()) < 0)
//		return (-1);
//	put_status(lst->index, time_eat, EATING);
//	printf("out pickup right\n");
	usleep(INTERVAL);
	while (!task_is_finished(l->last_meal, l->info->ms_eat))
	{
		if (is_end(l, l->last_meal))
			return (-1);
		usleep(INTERVAL);
	}
//	if (finish_eating(l))
//		return (-1);
	usleep(INTERVAL);
//	printf("task is finished\n");
	return (0);
}
