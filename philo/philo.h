/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/05 22:17:09 by hos              ###   ########.fr       */
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
# include <stdbool.h>

# define INTERVAL	200

enum e_status
{
	ONE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
};

typedef struct	s_info
{
	long		num_philo;
	long		ms_die;
	long		ms_eat;
	long		ms_sleep;
	long		num_to_eat;
}	t_info;

typedef struct	s_mt
{
	int	end_flag;
	long	*forks;
	pthread_mutex_t	*mt_forks;
	pthread_mutex_t	mt_end_flag;
	pthread_mutex_t	mt_write;
} t_mt;

typedef struct	s_lst
{
	long	index;
	int	status;
	long	last_meal;
	long	eat_count;
//	int	*fork;
	t_info	*info;
	t_mt *mt;
} t_lst;

//sleep_task.c
int	sleep_task(t_lst *l, long last_meal);

//is_end.c
bool	is_finished(long time_start, long time_task);
bool	is_end(t_lst *l, long last_meal);

//eat_task.c
long	eat_task(t_lst *l, long time_eat);

//put_status.c
int	put_status(t_lst *l, long time, int status);

//start_simulation.c
int	start_simulation(t_lst *l, long num_philo);

//free_all.c
int free_all(t_info *info, t_mt *mt, t_lst *l);

//save_argv.c
int	save_argv(int argc, char **argv, t_info **info);

//init_lst.c
int	init_lst(t_lst **l, t_info *info);

//utils.c
int	put_error(const char *str, int ret);
long	what_time(void);

//ft_utils.c
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int	ft_atol(const char *str);
int	ft_isdigit(int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
