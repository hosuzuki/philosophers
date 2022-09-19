/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_watcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:44:12 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 16:45:51 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*death_handler(void *arg)
{
	t_lst	*l;
	long	tmp;

	l = (t_lst *)arg;
	pthread_mutex_lock(l->philo);
	tmp = l->last_meal;
	pthread_mutex_unlock(l->philo);
	while (what_time() - tmp <= l->info->ms_die)
	{
		pthread_mutex_lock(l->philo);
		if (tmp != l->last_meal)
		{
			pthread_mutex_unlock(l->philo);
			return (NULL);
		}
		pthread_mutex_unlock(l->philo);
		usleep(200);
	}
	pthread_mutex_lock(l->writer);
	if (is_end(l))
	{
		pthread_mutex_unlock(l->writer);
		return (NULL);
	}
//	put_status(l, what_time(), DEAD);
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
