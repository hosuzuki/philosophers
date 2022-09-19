/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 17:00:30 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_eat_num_all(t_lst *l)
{
	long	i;

	i = 0;
	while (i <= l->info->num_philo - 1 \
			&& l->flags->num_to_eat_flags[i] == 1)
		i++;
	if (i == l->info->num_philo)
		return (1);
	return (0);
}

int	update_for_eat(t_lst *l)
{
	l->eat_count++;
	if (l->eat_count == l->info->num_to_eat)
	{
		pthread_mutex_lock(l->flag);
		l->flags->num_to_eat_flags[l->index - 1] = 1;
		if (count_eat_num_all(l) == 1)
		{
			l->flags->end_flag = OVER_EAT_COUNT;
			pthread_mutex_unlock(l->flag);
			return (-1);
		}
		pthread_mutex_unlock(l->flag);
	}
	return (0);
}

static int	put_log(t_lst *l, long time, int status)
{
	if (status == ONE_FORK)
		printf("%ld %ld has taken a fork\n", time, l->index);
	else if (status == EATING)
		printf("%ld %ld is eating\n", time, l->index);
	else if (status == SLEEPING)
		printf("%ld %ld is sleeping\n", time, l->index);
	else if (status == THINKING)
		printf("%ld %ld is thinking\n", time, l->index);
	else if (status == DEAD)
		printf("%ld %ld died\n", time, l->index);
	return (0);
}

int	put_status(t_lst *l, long time, int status)
{
	pthread_mutex_lock(l->writer);
	if (is_end(l))
	{
		pthread_mutex_unlock(l->writer);
		return (-1);
	}
	put_log(l, time, status);
	if (status == EATING)
	{
		if (update_for_eat(l) == -1)
		{
			pthread_mutex_unlock(l->writer);
			return (-1);
		}
	}
	pthread_mutex_unlock(l->writer);
	return (0);
}
