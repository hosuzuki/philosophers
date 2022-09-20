/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_task.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/20 11:15:38 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_task(t_lst *l)
{
	long	now;

	now = what_time();
	sem_wait(l->sem->writer);
	printf("%ld %ld is sleeping\n", now, l->index);
	sem_post(l->sem->writer);
	while (!task_is_finished(now, l->info->ms_sleep))
		usleep(INTERVAL);
	return (0);
}
