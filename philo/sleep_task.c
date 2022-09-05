/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_task.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/05 22:18:28 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_task(t_lst *l, long last_meal)
{
	long	time_sleep;

	if ((time_sleep = what_time()) < 0)
		return (-1);
	put_status(l, time_sleep, SLEEPING);
	while (!task_is_finished(time_sleep, l->info->ms_sleep))
	{
		if (is_end(l, last_meal))
			return (-1);
		usleep(INTERVAL);
	}
	return (0);
}
