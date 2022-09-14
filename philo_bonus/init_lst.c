/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/14 22:43:06 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	activate_sem(t_sem *sem, long num_philo)
{
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_WRITE);
	errno = 0;
	sem->fork = sem_open(SEM_NAME, O_CREAT | O_EXCL, 777, num_philo);
	sem->sem_write =sem_open(SEM_WRITE, O_CREAT | O_EXCL, 777, 1); 
	if (errno != 0)
		return (-1);
	return (0);
}

static int	init_sem(t_sem **sem, long num_philo)
{
	*sem = (t_sem *)malloc(sizeof(t_sem));
	if (!(*sem))
		return (-1);
	if (activate_sem(*sem, num_philo) < 0)
		return (-1);
	return (0);
}

int	init_lst(t_lst **l, t_info *info)
{
	long	i;
	t_sem	*sem;

	if (init_sem(&sem, info->num_philo) < 0)
		return (free_all(info, NULL, NULL));
	*l = (t_lst *)malloc(sizeof(t_lst) * info->num_philo);
	if (!(*l))
		return (free_all(info, sem, NULL));
	i = 0;
	while (i < info->num_philo)
	{
		(*l)[i].index = i + 1;
		(*l)[i].last_meal = 0;
		(*l)[i].info = info;
		(*l)[i++].sem = sem;
	}
	return (0);
}
