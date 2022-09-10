/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/10 18:37:48 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_flag_checker(t_lst *l)
{
	pthread_mutex_lock(&(l->mt->mt_end_flag));
	if (l->mt->end_flag == DEAD || l->mt->end_flag == OVER_EAT_COUNT)
	{
		pthread_mutex_unlock(&(l->mt->mt_end_flag));
		return (1);
	}
	pthread_mutex_unlock(&(l->mt->mt_end_flag));
	return (0);
}

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

void	raise_end_flag(t_lst *l, int status)
{
	pthread_mutex_lock(&(l->mt->mt_end_flag));
	l->mt->end_flag = status;
	pthread_mutex_unlock(&(l->mt->mt_end_flag));
}

bool	is_end(t_lst *l, long last_meal)
{
	long	time_now;

	if (l->mt->end_flag == DEAD || l->mt->end_flag == OVER_EAT_COUNT)
		return (true);
	time_now = what_time();
	if (time_now < 0 || time_now - last_meal >= l->info->ms_die)
	{
		put_status(l, time_now, DEAD);
		return (true);
	}
	return (false);
}
