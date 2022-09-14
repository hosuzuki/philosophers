/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_task.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/14 23:35:21 by hos              ###   ########.fr       */
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
	sem_wait(l->sem->sem_write);
	printf("%ld %ld died\n", what_time(), l->index);
	exit(1);
	return (NULL);
}

static void	activate_death_watcher(t_lst *l)
{
	pthread_t	tmp;

	pthread_create(&tmp, NULL, death_handler, l);
	pthread_detach(tmp);
}

int	pickup_forks(t_lst *l)
{
	activate_death_watcher(l);
	sem_wait(l->sem->fork);
	sem_wait(l->sem->sem_write);
	printf("%ld %ld has taken a fork\n", what_time(), l->index);
	sem_post(l->sem->sem_write);
	sem_wait(l->sem->fork);
	sem_wait(l->sem->sem_write);
	l->last_meal = what_time();
	printf("%ld %ld is eating\n", l->last_meal, l->index);
	sem_post(l->sem->sem_write);
	return (0);
}

long	eat_task(t_lst *l)
{
	pickup_forks(l);
	while (!task_is_finished(l->last_meal, l->info->ms_eat))
		usleep(INTERVAL);
	sem_post(l->sem->fork);
	sem_post(l->sem->fork);
	if (l->info->num_to_eat != -1)
	{
		l->info->num_to_eat--;
		if (l->info->num_to_eat == 0)
			exit(0);
	}
	return (0);
}
