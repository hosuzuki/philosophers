/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 17:16:28 by hos              ###   ########.fr       */
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

long	what_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (-1);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	put_error(const char *str, int ret)
{
	printf("ERROR: %s\n", str);
	return (ret);
}
