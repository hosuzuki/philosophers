/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:57:15 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 16:24:53 by hos              ###   ########.fr       */
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
	free_all(info, l->flags, data, l);
	return (0);
}
