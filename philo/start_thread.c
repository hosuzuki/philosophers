/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/08/31 22:40:13 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_thread(void *philo_arg) //arg is from pthread_create
{
	t_lst	*lst;
	long	start_to_eat;
	long	start_to_think;

	lst = (t_lst *)philo_arg;// why this is needed?
	if ((start_to_eat = return_time()) < 0)
		return (NULL);
	if (lst->index % 2) // ?
		usleep (200);
	while (1)
	{
		if ((start_to_eat = do_eat(lst, start_to_eat)) < 0)
			return (NULL);
		if (do_sleep(lst, start_to_eat) < 0)
			return (NULL);
		if ((start_to_think = return_time()) < 0)
			return (NULL);
		philo_putstatus(lst->index, start_to_think, PHILO_S_THINKING);
	}
	return (NULL);
}
