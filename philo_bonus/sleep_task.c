/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_task.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/14 22:53:17 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_task(t_lst *l)
{
	long	now;

	now = what_time();
	if (now < 0)
		put_error_and_exit("what_time", -1);
	sem_wait(l->sem->sem_write);
	printf("%ld %ld is sleeping\n", now, l->index);
	sem_post(l->sem->sem_write);
	while (!task_is_finished(now, l->info->ms_sleep))
		usleep(INTERVAL);
	return (0);
}
