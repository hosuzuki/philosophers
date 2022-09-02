/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/02 18:13:30 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(void *philo_arg) 
//arg is from pthread_create
{
	t_lst	*lst;
	long	start_to_eat;
	long	start_to_think;

	lst = (t_lst *)philo_arg;// why this is needed?
	if ((start_to_eat = return_time()) < 0)
		return (NULL);
	if (lst->index % 2) // ?
		usleep (200);
	while (1)
	{
		if ((start_to_eat = do_eat(lst, start_to_eat)) < 0)
			return (NULL);
		if (do_sleep(lst, start_to_eat) < 0)
			return (NULL);
		if ((start_to_think = return_time()) < 0)
			return (NULL);
		philo_putstatus(lst->index, start_to_think, PHILO_S_THINKING);
	}
	return (NULL);
}

int	start_simulation(t_lst *l, long num_philo)
{
	long	i;
	pthread_t *philos;

	philos = (pthread_t *)malloc(sizeof(pthread_t) * num_philo);
	if (!philo)
		return (free_all(l->info, l->mt, l);
	i = 0;
	while (i < num_philo)
	{
		pthread_create(&philos[i], NULL, activate_philo, &l[i]);
		i++;
	}
	i = 0;
	while (i < num_philo)
		pthread_join(&philos[i++], NULL);
//	philo_mutex_destroy();
	return();
}
