/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 14:38:44 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_each_lst(t_lst **l, t_info *info, \
		t_flags *flags, t_data *data)
{
	long	i;

	i = 0;
	while (i < info->num_philo)
	{
		(*l)[i].index = i + 1;
		(*l)[i].last_meal = 0;
		(*l)[i].eat_count = 0;
		(*l)[i].philo = &(data->philos[i]);
		(*l)[i].left_fork = &(data->forks[i]);
//		printf("%ld, left: %ld, right: %ld\n", 
//		i + 1, i, (i + 1) % info->num_philo);
		(*l)[i].right_fork = &(data->forks[(i + 1) % info->num_philo]);
		(*l)[i].writer = &(data->writer);
		(*l)[i].flag = &(data->flag);
		(*l)[i].info = info;
		(*l)[i++].flags = flags;
//		(*l)[i - 1].flags->end_flag = 0; //delete this later
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
	return (0);
//	(*data)->writer = NULL;
}

static int	init_flags(t_flags **flags, long num_philo)
{
	long	i;

	*flags = (t_flags *)malloc(sizeof(t_flags));
	if (!(*flags))
		return (-1);
	(*flags)->end_flag = 0;
	(*flags)->num_to_eat_flags = (int *)malloc(sizeof(int) * \
		num_philo);
	if (!(*flags)->num_to_eat_flags)
	{
		free (*flags);
		return (-1);
	}
	i = 0;
	while (i < num_philo)
		(*flags)->num_to_eat_flags[i++] = 0;
	return (0);
}

int	init_lst(t_info *info, t_data **data, t_lst **l)
{
	t_flags	*flags;

	if (init_flags(&flags, info->num_philo) < 0)
		return (free_all(info, NULL, NULL, NULL));
	if (init_data(data, info->num_philo) < 0)
		return (free_all(info, flags, NULL, NULL));
	*l = (t_lst *)malloc(sizeof(t_lst) * info->num_philo);
	if (!(*l))
		return (free_all(info, flags, *data, NULL));
	if (activate_mutex(*data, info->num_philo) < 0)
		return (free_all(info, flags, *data, NULL));
	init_each_lst(l, info, flags, *data);
	return (0);
}
