/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/08/31 21:42:48 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_sleep(t_lst *lst, long start_to_eat)
{
	long	start_to_sleep;

	if ((start_to_sleep = return_time()) < 0)
		return (-1);
	philo_putstatus(lst->index, start_to_sleep, PHILO_S_SLEEPING);
	while (!philo_has_finished(start_to_sleep, lst->sleep))
	{
		if (philo_check_dead(lst, start_to_eat))
			return (-1);
		usleep(PHILO_WHILE_INTERVAL_USEC);
	}
	return (0);
}
