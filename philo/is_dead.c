/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/05 22:12:12 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
bool	over_num_to_eat(t_lst *l)
{
	if (l->info->num_to_eat <= l->eat_count)
		
	if (all
}
*/

bool	is_finished(long time_start, long time_task)
{
	long time_now;

	if ((time_now = what_time()) < 0)
		return (false);
	if (time_now - time_start >= time_task)
		return (false);
	return (true);
}

bool	is_end(t_lst *l, long time_eat)
{
	long	time_now;

	if (l->mt->end_flag == 1)
		return (true);
	if ((time_now = what_time()) < 0 || \
		time_now - time_eat > l->info->ms_die)
	{
		pthread_mutex_lock(&(l->mt->mt_end_flag));
		l->mt->end_flag = 1;
		pthread_mutex_unlock(&(l->mt->mt_end_flag));
		put_status(l, time_now, DEAD);
		return (true);
	}
//	if (over_num_to_eat(l)
//		return (true);
	return (false);
}
