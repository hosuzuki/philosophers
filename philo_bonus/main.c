/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:57:15 by hos               #+#    #+#             */
/*   Updated: 2022/09/14 23:05:32 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	*info;
	t_lst	*l;

	if (save_argv(argc, argv, &info) < 0)
		return (-1);
	if (init_lst(&l, info) < 0)
		return (-1);
	if (start_simulation(l, l->info->num_philo) < 0)
		return (-1);
	free_all(info, l->sem, l);
	return (0);
}
