/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 20:12:23 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	activate_sem(t_sem *sem, long num_philo)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITER);
	sem_unlink(SEM_MEAL_FLAGS);
	errno = 0;
	sem->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 777, num_philo);
	sem->writer = sem_open(SEM_WRITER, O_CREAT | O_EXCL, 777, 1);
	sem->meal_flags = sem_open(SEM_MEAL_FLAGS, O_CREAT | O_EXCL, 777, num_philo);
	if (errno != 0)
		put_error_and_exit("sem_open", -1);
	return (0);
}

static int	init_sem(t_sem **sem, long num_philo)
{
	*sem = (t_sem *)malloc(sizeof(t_sem));
	if (!(*sem))
		put_error_and_exit("malloc", -1);
	activate_sem(*sem, num_philo);
	return (0);
}

int	init_lst(t_lst **l, t_info *info)
{
	long	i;
	t_sem	*sem;

	init_sem(&sem, info->num_philo);
	*l = (t_lst *)malloc(sizeof(t_lst) * info->num_philo);
	if (!(*l))
		put_error_and_exit("malloc", -1);
	i = 0;
	while (i < info->num_philo)
	{
		(*l)[i].index = i + 1;
		(*l)[i].last_meal = 0;
		(*l)[i].meal_flag = &(sem->meal_flags[i]);
		printf("meal_flag: %p\n", &(sem->meal_flags[i]));
		(*l)[i].info = info;
		(*l)[i++].sem = sem;
	}
	return (0);
}
