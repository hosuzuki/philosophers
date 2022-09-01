/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/01 17:46:34 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>

# define INTERVAL	200

enum e_status
{
	ONE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
};

typedef struct	s_lst
{
	long		num_philo;
	long		die;
	long		eat;
	long		sleep;
	long		num_to_eat;
}	t_lst;

typedef struct	s_thrd
{
	long	index;
	int		end_flag;
	int	*fork;
	pthread_mutex_t	*mt_fork;
	pthread_mutex_t	mt_end_flag;
	pthread_mutex_t	mt_write;
} t_thrd;




#endif
