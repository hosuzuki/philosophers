/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:57:15 by hos               #+#    #+#             */
/*   Updated: 2022/09/18 23:06:27 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	*info;
	t_data	*data;
	t_lst		*l;

	if (save_argv(argc, argv, &info) < 0)
		return (-1);
	if (init_lst(info, &data, &l) < 0)
		return (-1);
	if (start_simulation(data, l, info->num_philo) < 0)
		return (-1);
	free_all(info, l->mt, l);
	return (0);
}
