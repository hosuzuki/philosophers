/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/11 16:35:33 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	task_is_finished(long time_start, long duration)
{
	long	time_now;

	time_now = what_time();
	if (time_now < 0)
		return (false);
	if (time_now - time_start < duration)
		return (false);
	return (true);
}

bool	is_end_flag_up(t_lst *l)
{
	pthread_mutex_lock(&(l->mt->mt_end_flag));
	if (l->mt->end_flag == DEAD || l->mt->end_flag == OVER_EAT_COUNT)
	{
		pthread_mutex_unlock(&(l->mt->mt_end_flag));
		return (true);
	}
	pthread_mutex_unlock(&(l->mt->mt_end_flag));
	return (false);
}

void	raise_end_flag(t_lst *l, int status)
{
//	long	i;

	pthread_mutex_lock(&(l->mt->mt_end_flag));
	l->mt->end_flag = status;
	pthread_mutex_unlock(&(l->mt->mt_end_flag));
//	i = 0;
//	usleep(200);
//	while (i < l->info->num_philo)
//		pthread_mutex_unlock(&(l->mt->mt_forks[i++]));
}

static bool	is_over_time_to_die(long time_now, t_lst *l)
{
	if (time_now - l->last_meal >= l->info->ms_die)
		return (true);
	return (false);
}

bool	is_end(t_lst *l)
{
	long	time_now;

	if (is_end_flag_up(l) == true)
		return (true);
	time_now = what_time();
	if (time_now < 0)
		return (false);
	if (is_over_time_to_die(time_now, l) == true)
	{
		put_status(l, time_now, DEAD);
		return (true);
	}
	return (false);
}
