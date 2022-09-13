/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_task.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/11 13:34:21 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_task(t_lst *l)
{
	long	time_sleep;

	time_sleep = what_time();
	if (time_sleep < 0)
		return (-1);
	if (put_status(l, time_sleep, SLEEPING) < 0)
		return (-1);
	while (!task_is_finished(time_sleep, l->info->ms_sleep))
	{
		if (is_end(l))
			return (-1);
		usleep(INTERVAL);
	}
	return (0);
}
