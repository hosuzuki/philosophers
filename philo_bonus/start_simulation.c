/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/14 23:34:55 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_and_destroy_sem(t_lst l, pid_t *pids, long num_philo)
{
	long	i;
	int		status;

	i = 0;
	while (i < num_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1 || WEXITSTATUS(status) == -1)
		{
			i = 0;
			while (i < num_philo)
				kill(pids[i++], SIGINT);
			break ;
		}
		i++;
	}
	sem_close(l.sem->fork);
	sem_close(l.sem->sem_write);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_WRITE);
}

static void	life_of_philo(t_lst *l)
{
	l->last_meal = what_time();
	while (1)
	{
		eat_task(l);
		sleep_task(l);
		sem_wait(l->sem->sem_write);
		printf("%ld %ld is thinking\n", what_time(), l->index);
		sem_post(l->sem->sem_write);
	}
	return ;
}

static pid_t	create_process(t_lst l)
{
	pid_t	ret;

	ret = fork();
	if (ret < 0)
		put_error_and_exit("fork error", -1);
	else if (ret == 0)
		life_of_philo(&l);
	return (ret);
}

int	start_simulation(t_lst *l, long num_philo)
{
	long	i;
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * num_philo);
	if (!pids)
		put_error_and_exit("malloc", -1);
	i = 0;
	while (i < num_philo)
	{
		pids[i] = create_process(l[i]);
		i++;
	}
	wait_and_destroy_sem(l[0], pids, num_philo);
	free (pids);
	return (0);
}
