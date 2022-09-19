/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 16:25:39 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_all(t_info *info, t_flags *flags, t_data *data, t_lst *l)
{
	if (info)
		free (info);
	if (flags)
	{
		free(flags->num_to_eat_flags);
		free (flags);
	}
	if (data)
	{
		free (data->philos);
		free (data->forks);
		free (data);
	}
	if (l != NULL)
		free (l);
	return (-1);
}
