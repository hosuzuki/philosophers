/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/06 11:54:51 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	free_all(t_thrd *t, pthread_t *p, int ret)
{
	free (p);
	free (t->fork);
	free (t->mt_fork);
	free (t->fork_rsvd); // needed?
//	free (t);
//	what about lst?
	return (ret);
}
*/
int free_all(t_info *info, t_mt *mt, t_lst *l)
{
	if (info)
	{
		if (info->num_to_eat_flag)
			free (info->num_to_eat_flag);
		free (info);
	}
	if (mt)
	{
		free(mt->forks);
		free(mt->mt_forks);
		free (mt);
	}
	if (l)
		free (l);
	return (-1);
}
