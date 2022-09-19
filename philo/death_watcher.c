/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_watcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:44:12 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 17:05:20 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_alive(long tmp, t_lst *l)
{
	while (what_time() - tmp <= l->info->ms_die)
	{
		pthread_mutex_lock(l->philo);
		if (tmp != l->last_meal)
		{
			pthread_mutex_unlock(l->philo);
			return (1);
		}
		pthread_mutex_unlock(l->philo);
		usleep(200);
	}
	return (0);
}

static void	*death_handler(void *arg)
{
	t_lst	*l;
	long	tmp;

	l = (t_lst *)arg;
	pthread_mutex_lock(l->philo);
	tmp = l->last_meal;
	pthread_mutex_unlock(l->philo);
	if (is_alive(tmp, l) == 1)
		return (NULL);
	pthread_mutex_lock(l->writer);
	if (is_end(l))
	{
		pthread_mutex_unlock(l->writer);
		return (NULL);
	}
	pthread_mutex_lock(l->flag);
	l->flags->end_flag = DEAD;
	pthread_mutex_unlock(l->flag);
	printf("%ld %ld died\n", what_time(), l->index);
	pthread_mutex_unlock(l->writer);
	return (NULL);
}

void	activate_death_watcher(t_lst *l)
{
	pthread_t	tmp;

	pthread_create(&tmp, NULL, death_handler, l);
	pthread_detach(tmp);
}
