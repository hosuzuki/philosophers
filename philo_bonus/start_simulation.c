/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/20 08:15:48 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_sem(t_lst *l, char **names, long num_philo)
{
	long	i;

	sem_close(l->sem->forks);
	sem_close(l->sem->writer);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITER);
	i = 0;
	while (i < num_philo)
	{
		sem_close(l[i].meal_flag);
		sem_unlink(names[i++]);
	}
	return ;
}

static void	wait_process(pid_t *pids, long num_philo)
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
	return ;
}

static void	life_of_philo(t_lst *l)
{
	l->last_meal = what_time();
	activate_death_watcher(l);
	while (1)
	{
		errno = 0;
		eat_task(l);
		sleep_task(l);
		sem_wait(l->sem->writer);
		printf("%ld %ld is thinking\n", what_time(), l->index);
		sem_post(l->sem->writer);
		if (errno != 0)
			put_error_and_exit("sem", -1);
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

int	start_simulation(t_lst *l, long num_philo, char **names)
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
	wait_process(pids, num_philo);
	cleanup_sem(l, names, num_philo);
	free (pids);
	return (0);
}
