/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/13 16:37:27 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_all_sem(t_lst *l)
{
	sem_close(l->sem->fork);
	sem_close(l->sem->sem_end_flag);
	sem_close(l->sem->sem_write);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_END_FLAG);
	sem_unlink(SEM_WRITE);
}


void	*life_of_philo(t_lst *l)
{
//	t_lst	*l;
	long	time_think;

//	l = (t_lst *)arg;
//	if (l->index % 2)
//		usleep (2500);
	l->last_meal = what_time();
	if (l->last_meal < 0)
		return (NULL);
	while (1)
	{
		if (eat_task(l) < 0)
			return (test(l, "eat"));
		if (sleep_task(l) < 0)
			return (test(l, "sleep"));
		time_think = what_time();
		if (time_think < 0)
			return (NULL);
		if (put_status(l, time_think, THINKING) < 0)
			return (test(l, "think"));
	}
	return (NULL);
}

int	start_simulation(t_lst *l, long num_philo)
{
	int		status;
	long	i;
	long	j;
	pid_t	p;

	i = 0;
	while (i < num_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			life_of_philo(&l[i++]);
			exit (0);
		}
	}
	j = 0;
	while (j < num_philo)
	{
		waitpid(-1, &status, 0);
		j++;
	}
	destroy_all_sem(l);
	return (0);
}
