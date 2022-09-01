/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/08/31 22:39:21 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ctrl_mutex_fork(long index, long n_philo, char l_or_u)
{
	if (l_or_u == 'l')
	{
		pthread_mutex_lock(&g_mutex_fork[index]);
		pthread_mutex_lock(&g_mutex_fork[(index + 1) % n_philo]);
	}
	else if (l_or_u == 'u')
	{
		pthread_mutex_unlock(&g_mutex_fork[index]);
		pthread_mutex_unlock(&g_mutex_fork[(index + 1) % n_philo]);
	}
}

static int	finish_eating(t_lst *lst)
{
	int	flgend;

	flgend = 0;
	ctrl_mutex_fork(lst->index, lst->n_philo, 'l');
	g_fork[lst->index] = 0;
	g_fork[(lst->index + 1) % lst->n_philo] = 0;
	ctrl_mutex_fork(lst->index, lst->n_philo, 'u');
	if (lst->n_eat > 0)
	{
		lst->n_eat--;
		if (lst->n_eat == 0)
		{
			pthread_mutex_lock(&g_mutex_n_finished);
			g_n_finished++;
			if (g_n_finished == lst->n_philo)
			{
				pthread_mutex_lock(&g_mutex_flgend);
				g_flgend = 1 ;
				pthread_mutex_unlock(&g_mutex_flgend);
				flgend = 1;
			}
			pthread_mutex_unlock(&g_mutex_n_finished);
		}
	}
	return (flgend);
}

static int	fork_is_available(t_lst *lst)
{
	if (!g_fork[lst->index] && ! g_fork[(lst->index + 1) % lst->n_philo] 
			&& (g_fork_rsvd_by[lst->index] == lst->index
				|| g_fork_rsvd_by[lst->index] == 1)
			&& (g_fork_rsvd_by[(lst->index + 1) % lst->n_philo] == lst->index
				|| g_fork_rsvd_by[(lst->index + 1) % lst->n_philo] == -1))
		return (1);
	if (g_fork_rsvd_by[lst->index] == -1)
		g_fork_rsvd_by[lst->index] = lst->index;
	if (g_fork_rsvd_by[(lst->index + 1) % lst->n_philo] == -1)
		g_fork_rsvd_by[(lst->index + 1) % lst->n_philo] = lst->index;
	return (0);
}

static int	ft_fork(t_lst *lst)
{
	long	time_taken_fork;

	ctrl_mutex_fork(lst->index, lst->n_philo, 'l');
	if (fork_is_available(lst))
	{
		time_taken_fork = return_time();
		g_fork[lst->index] = 1;
		philo_putstatus(lst->index, time_taken_fork, PHILO_S_TAKENFORK);
		g_fork_rsvd_by[lst->index] = -1;
		g_fork[(lst->index + 1) % lst->n_philo] = -1;
		pthread_mutex_unlock(&g_mutex_fork[lst->index]);
		pthread_mutex_unlock(
				&g_mutex_fork[(lst->index + 1) % lst->n_philo]);
		return (1);
	}
	ctrl_mutex_fork(lst->index, lst->n_philo, 'u');
	return (0);
}

long	do_eat(t_lst *lst, long time_start_eating)
{
	while (!ft_fork(lst))
	{
		if (philo_check_dead(lst, time_start_eating))
			return (-1);
		usleep(PHILO_WHILE_INTERVAL_USEC);
	}
	if ((time_start_eating = return_time()) < 0)
		return (-1);
	philo_putstatus(lst->index, time_start_eating, PHILO_S_EATING);
	while (!philo_has_finished(time_start_eating, lst->eat))
	{
		if (philo_check_dead(lst, time_start_eating))
			return (-1);
		usleep(PHILO_WHILE_INTERVAL_USEC);
	}
	if (finish_eating(lst))
		return (-1);
	return (time_start_eating);
}
