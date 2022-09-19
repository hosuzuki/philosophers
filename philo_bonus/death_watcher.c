/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_watcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:02:20 by hos               #+#    #+#             */
/*   Updated: 2022/09/20 08:01:22 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*death_handler(void *arg)
{
	t_lst	*l;
	long	time;

	l = (t_lst *)arg;
	sem_wait(l->meal_flag);
	time = l->last_meal;
	sem_post(l->meal_flag);

	while (what_time() - time <= l->info->ms_die)
	{
		sem_wait(l->meal_flag);
//		printf("death_loop2:%ld\n", l->index);
		if (time != l->last_meal)
		{
//			printf("death_loop3:%ld\n", l->index);
			sem_post(l->meal_flag);
			return (NULL);
		}
		sem_post(l->meal_flag);
		usleep(INTERVAL);
	}
	sem_wait(l->sem->writer);
	if (errno != 0)
		put_error_and_exit("sem", -1);
	printf("%ld %ld died\n", what_time(), l->index);
	exit(1);
	return (NULL);
}

void	activate_death_watcher(t_lst *l)
{
	pthread_t	tmp;

	if (pthread_create(&tmp, NULL, death_handler, l))
		put_error_and_exit("pthread_create", -1);
	if (pthread_detach(tmp))
		put_error_and_exit("pthread_detatch", -1);
}
