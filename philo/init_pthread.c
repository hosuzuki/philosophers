/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_pthread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/08/31 20:35:22 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex_fork(t_thrd *t, long n_philo)
{
	long	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&t->mt_fork[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&t->mt_fork[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	init_mutex(t_thrd *t, long n_philo)
{
	if (pthread_mutex_init(&t->mt_flgend, NULL))
		return (-1);
	if (pthread_mutex_init(&t->mt_n_finished, NULL))
	{
		pthread_mutex_destroy(&t->mt_flgend);
		return (-1);
	}
	if (pthread_mutex_init(&t->mt_write, NULL))
	{
		pthread_mutex_destroy(&t->mt_flgend);
		pthread_mutex_destroy(&t->mt_n_finished);
		return (-1);
	}
	if (init_mutex_fork(t, n_philo))
	{
		pthread_mutex_destroy(&t->mt_flgend);
		pthread_mutex_destroy(&t->mt_n_finished);
		pthread_mutex_destroy(&t->mt_write);
		return (-1);
	}
	return (0);
}

int	init_pthread(t_thrd *t, pthread_t **p, long n_philo)
{
	int	i;

	*p = (pthread_t *)malloc(sizeof(pthread_t) * n_philo);
	if (!(*p))
		return (-1);
	t->flgend = 0;
	t->mt_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_philo);
	t->fork = (int *)malloc(sizeof(int) * n_philo);
	t->fork_rsvd = (int *)malloc(sizeof(int) * n_philo);
	//t->n_finised = 0; I just added
	if (!t->mt_fork || !t->fork || !t->fork_rsvd)
		return (-1);
	i = 0;
	while (i < n_philo)
	{
		t->fork[i] = 0;
		t->fork_rsvd[i] = -1;
		i++;
	}
//	printf("ft_init_pthread\n");
	if (init_mutex(t, n_philo) < 0)
		return (-1);
	return (0);
}
