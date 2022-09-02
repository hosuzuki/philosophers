/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/02 17:49:10 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	activate_mutex_forks(t_mt *mt, long num_philo)
{
	long	i;

	i = 0;
	while (i < num_philo)
	{
		if (pthread_mutex_init(&mt->mt_forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&mt->mt_forks[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	activate_mutex(t_mt *mt, long num_philo)
{
	if (pthread_mutex_init(&mt->mt_end_flag, NULL))
		return (-1);
	if (pthread_mutex_init(&mt->mt_write, NULL))
	{
		pthread_mutex_destroy(&mt->mt_end_flag);
		return (-1);
	}
	if (activate_mutex_forks(mt, num_philo))
	{
		pthread_mutex_destroy(&mt->mt_end_flag);
		pthread_mutex_destroy(&mt->mt_write);
		return (-1);
	}
	return (0);
}

static int	init_forks(t_mt *mt, long num_philo)
{
	mt->forks = (long *)malloc(sizeof(long) * num_philo);
	if (!mt->forks)
	{
		free(mt);
		return (-1);
	}
	mt->mt_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philo);
	if (!mt->mt_forks)
	{
		free(mt->forks);
		free(mt);
		return (-1);
	}
	return (0);
}

static int	init_mt(t_mt **mt, long num_philo)
{
	*mt = (t_mt *)malloc(sizeof(t_mt));
	if (!(*mt))
		return (-1);
	(*mt)->end_flag = 0;
	if (init_forks(*mt, num_philo) < 0)
		return (-1); 
	if (activate_mutex(*mt, num_philo) < 0)
		return (-1);
	return (0);
}

int	init_lst(t_lst **l, t_info *info)
{
	long	i;
	t_mt	*mt;

	if (init_mt(&mt, info->num_philo) < 0)
		return (free_all(info, NULL, NULL));
	*l = (t_lst *)malloc(sizeof(t_lst) * info->num_philo);
	if (!(*l))
		return (free_all(info, mt, NULL));
	i = 0;
	while (i < info->num_philo)
	{
		(*l)[i].index = i + 1;
		(*l)[i].status = THINKING;
		(*l)[i].last_meal = what_time();
		(*l)[i].eat_count = 0;
		(*l)[i].info = info;
		(*l)[i++].mt = mt;
	}
	return (0);
}
