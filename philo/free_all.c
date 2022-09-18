/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/18 22:18:22 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_all(t_info *info, t_share *share, t_data *data, t_lst *l)
{
	if (info)
		free (info);
	if (share)
	{
		free(share->num_to_eat_flags);
		free (share);
	}
	if (data)
	{
		free (data->eat_lock);
		free (data->forks);
		free (data);
	}
	if (l)
		free (l);
	return (-1);
}
