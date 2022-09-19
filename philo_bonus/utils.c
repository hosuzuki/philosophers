/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/20 07:34:52 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_error_and_exit(const char *str, int ret)
{
	printf("ERROR: %s\n", str);
	exit (ret);
}

long	what_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		put_error_and_exit("what_time", -1);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

bool	task_is_finished(long time_start, long duration)
{
	if (what_time() - time_start < duration)
		return (false);
	return (true);
}

int	free_all(t_info *info, t_sem *sem, t_lst *l, char **names)
{
	long	i;

	i = 0;
	if (names)
	{
		while (i < info->num_philo)
			free(names[i++]);
		free(names);
	}
	if (info)
		free (info);
	if (sem)
		free (sem);
	if (l)
		free (l);
	return (-1);
}
