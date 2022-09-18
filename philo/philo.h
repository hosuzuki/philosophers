/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/18 14:25:09 by hos              ###   ########.fr       */
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
# include <errno.h>

# define INTERVAL	800

enum e_status
{
	ONE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	OVER_EAT_COUNT,
};

typedef struct s_info
{
	long	num_philo;
	long	ms_die;
	long	ms_eat;
	long	ms_sleep;
	long	num_to_eat;
	int		*num_to_eat_flag;
}	t_info;

typedef struct s_mt
{
	int				end_flag;
	long			*forks;
	pthread_mutex_t	*mt_forks;
	pthread_mutex_t	mt_end_flag;
	pthread_mutex_t	mt_write;
}	t_mt;

typedef struct s_lst
{
	long	index;
	int		status;
	long	last_meal;
	long	eat_count;
	t_info	*info;
	t_mt	*mt;
}	t_lst;

//sleep_task.c
int		sleep_task(t_lst *l);

//is_end.c
bool	is_end_flag_up(t_lst *l);
bool	task_is_finished(long time_start, long duration);
bool	is_end(t_lst *l);
void	raise_end_flag(t_lst *l, int status);
int		end_flag_checker(t_lst *l);

//eat_task.c
void	activate_death_watcher(t_lst *l);
long	eat_task(t_lst *l);

//put_status.c
int		put_status(t_lst *l, long time, int status);

//start_simulation.c
int		start_simulation(t_lst *l, long num_philo);

//free_all.c
int		free_all(t_info *info, t_mt *mt, t_lst *l);

//save_argv.c
int		save_argv(int argc, char **argv, t_info **info);

//init_lst.c
int		init_lst(t_lst **l, t_info *info);

//utils.c
int		put_error(const char *str, int ret);
long	what_time(void);

//ft_utils.c
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_atol(const char *str);

#endif
