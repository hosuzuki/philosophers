/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:57:15 by hos               #+#    #+#             */
/*   Updated: 2022/09/01 17:50:51 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
//	long	n_philo;
	t_lst	*lst;
	pthread_t	*p;
	t_thrd	t;

	if (save_argv(argc, argv, &lst) < 0)
		return (-1);
	if (init_pthread(&t, &p, lst->n_philo) < 0)
		return (free_all(&t, NULL, 1));
	i = 0;
	while (i < lst[0].n_philo)
	{
		pthread_create(&p[i], NULL, start_thread, &lst[i]);
		i++;
	}
	return (0);
/*
	i = 0;
	while (i < n_philo)
		pthread_join(philo_pthread[i++], NULL);
	philo_mutex_destroy(n_philo);
	return (philo_free_ret(philo, philo_pthread, 1));
*/
}
