/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_dead.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/08/31 22:28:07 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	philo_check_dead(t_lst *lst, long time_start_eating)
{
	long	time_now;

	pthread_mutex_lock(&g_mutex_flgend);
	if (g_flgend)
	{
		pthread_mutex_unlock(&g_mutex_flgend);
		return (1);
	}
	if ((time_now = return_time()) < 0 || time_now - time_start_eating > lst->die)
	{
		g_flgend = 1;
		pthread_mutex_unlock(&g_mutex_flgend);
		philo_putstatus(lst->index, time_now, PHILO_S_DEAD);
		return (1);
	}
	pthread_mutex_unlock(&g_mutex_flgend);
	return (0);
}
