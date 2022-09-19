/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 15:52:11 by hos              ###   ########.fr       */
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

/*
 void	raise_end_flag(t_lst *l, int status)
{
//	pthread_mutex_lock(l->);
	l->flags->end_flag = status;
//	pthread_mutex_unlock(l->);
}
*/

bool	is_end(t_lst *l)
{
	pthread_mutex_lock(l->flag);
	if (l->flags->end_flag == DEAD || \
		l->flags->end_flag == OVER_EAT_COUNT)
	{
		pthread_mutex_unlock(l->flag);
		return (true);
	}
	pthread_mutex_unlock(l->flag);
	return (false);
}
