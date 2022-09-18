/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/18 22:52:21 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_each_lst(t_lst **lst, t_info *info, \
		t_share *share, t_data *data)
{
	long	i;

	i = 0;
	while (i < info->num_philo)
	{
		(*l)[i].index = i + 1;
		(*l)[i].last_meal = 0;
		(*l)[i].eat_count = 0;
		(*l)[i].philo = &(data->philos[i]);
		(*l)[i].left_fork = &(data->forks[index - 1]);
		(*l)[i].right_fork = &(data->forks[index % info->num_philo]);
		(*l)[i].writer = &(data->writer);
		(*l)[i].share = &(data->share);
(*l)[i].info = info;
		(*l)[i++].share = share;
	}
}

static int	init_data(t_data **data, long num_philo)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!(*data))
		return (-1);
	(*data)->philos = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* num_philo);
	if (!(*data)->philos)
	{
		free (*data);
		return (-1);
	}
	(*data)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* num_philo);
	if (!(*data)->forks)
	{
		free ((*data)->philos);
		free (*data);
		return (-1);
	}
	(*data)->writer = NULL;
}

static int	init_share(t_share **share, long num_philo)
{
	long	i;

	*share = (t_share *)malloc(sizeof(t_share));
	if (!(*share))
		return (-1);
	(*share)->end_flag = 0;
	(*share)->num_to_eat_flags = (int *)malloc(sizeof(int) * \
		num_philo);
	if (!(*share)->num_to_eat_flag)
	{
		free (*share);
		return (-1);
	}
	while (i < num_philo)
		(*share)->num_to_eat_flag[i] = 0;
	return (0);
}

int	init_lst(t_info *info, t_data **data, t_lst **l)
{
	t_share	*share;

	if (init_share(&share, info->num_philo) < 0)
		return (free_all(info, NULL, NULL, NULL));
	if (init_data(data, info->num_philo) < 0)
		return (free_all(info, share, NULL, NULL));
	*l = (t_lst *)malloc(sizeof(t_lst) * info->num_philo);
	if (!(*l))
		return (free_all(info, share, *data, NULL));
	if (activate_mutex(data, info->num_philo) < 0)
		return (free_all(info, share, *data, NULL));
	init_each_lst(info, share, *data);
	return (0);
}
