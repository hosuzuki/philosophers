/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 17:09:49 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	task_is_finished(long time_start, long duration)
{
	if (what_time() - time_start < duration)
		return (false);
	return (true);
}

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
