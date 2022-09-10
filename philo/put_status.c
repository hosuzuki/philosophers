/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/10 18:45:09 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_eat_num_all(t_lst *l)
{
	long	i;

	i = 0;
	while (i <= l->info->num_philo - 1 \
			&& l->info->num_to_eat_flag[i] == 1)
		i++;
	if (i == l->info->num_philo)
		return (1);
	return (0);
}

int	update_for_eat(t_lst *l)
{
	l->status = EATING;
	l->eat_count++;
	if (l->eat_count == l->info->num_to_eat)
	{
		l->info->num_to_eat_flag[l->index - 1] = 1;
		if (count_eat_num_all(l) == 1)
		{
			raise_end_flag(l, OVER_EAT_COUNT);
			return (-1);
		}
	}
	return (0);
}

int	update_status(t_lst *l, int status)
{
	if (status == EATING)
	{
		if (update_for_eat(l) == -1)
			return (-1);
	}
	else if (status == ONE_FORK)
		l->status = ONE_FORK;
	else if (status == SLEEPING)
		l->status = SLEEPING;
	else if (status == THINKING)
		l->status = THINKING;
	else if (status == DEAD)
	{
		raise_end_flag(l, DEAD);
		return (-1);
	}
	return (0);
}

int	put_status(t_lst *l, long time, int status)
{
	char	*ret;

	ret = create_str_to_put(l, time, status);
	if (!ret || end_flag_checker(l) == 1)
		return (-1);
	pthread_mutex_lock(&(l->mt->mt_write));
	write(1, ret, ft_strlen(ret));
	pthread_mutex_unlock(&(l->mt->mt_write));
	if (update_status(l, status) == -1)
		return (-1);
	free (ret);
	return (0);
}
