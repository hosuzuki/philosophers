/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_task.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/05 22:13:02 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_task(t_lst *l, long time_eat)
{
	long	time_sleep;

	if ((time_sleep = what_time()) < 0)
		return (-1);
	put_status(l, time_sleep, SLEEPING);
	while (!is_finished(time_sleep, l->info->ms_sleep))
	{
		if (is_end(l, time_eat))
			return (-1);
		usleep(INTERVAL);
	}
	return (0);
}
