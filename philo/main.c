/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:57:15 by hos               #+#    #+#             */
/*   Updated: 2022/09/02 19:56:42 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
//	long	n_philo;
	//pthread_t	*p;
	t_info	*info;
	t_lst	*l;

	if (save_argv(argc, argv, &info) < 0)
		return (-1);
/*	printf("info->num_philo: %ld\n", info->num_philo);
	printf("info->ms_die: %ld\n", info->ms_die);
	printf("info->ms_eat: %ld\n", info->ms_eat);
	printf("info->ms_sleep: %ld\n", info->ms_sleep);
	printf("info->num_to_eat: %ld\n", info->num_to_eat);
*/	
	if (init_lst(&l, info) < 0)
		return (-1);
/*	printf("l[0].index: %ld\n", l[0].index);
	printf("l[1].index: %ld\n", l[1].index);
	printf("l[0]->mt.end_flag: %d\n", l[0].mt->end_flag);
	printf("l[1]->mt.end_flag: %d\n", l[1].mt->end_flag);
*/
	if (start_simulation(l, l->info->num_philo);
		return (-1);
	}
	free_all(info, l->mt, l);
	return (0);
}
