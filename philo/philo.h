/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 15:52:19 by hos              ###   ########.fr       */
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

# define INTERVAL	200

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
}	t_info;

typedef struct s_flags
{
	int				end_flag;
	int				*num_to_eat_flags;
}	t_flags;

typedef struct s_lst
{
	long			index;
	long			last_meal;
	long			eat_count;
	pthread_mutex_t	*philo;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t	*writer;
	pthread_mutex_t	*flag;
	t_info		*info;
	t_flags		*flags;
}	t_lst;

typedef struct s_data
{
	pthread_mutex_t	flag;
	pthread_mutex_t	writer;
	pthread_mutex_t	*philos;
	pthread_mutex_t	*forks;
} t_data;

//sleep_task.c
int		sleep_task(t_lst *l);

//is_end.c
//bool	is_end_flag_up(t_lst *l);
bool	task_is_finished(long time_start, long duration);
bool	is_end(t_lst *l);
//void	raise_end_flag(t_lst *l, int status);
//int		end_flag_checker(t_lst *l);

//eat_task.c
long	eat_task(t_lst *l);

//death_wather.c
void	activate_death_watcher(t_lst *l);

//put_status.c
int		put_status(t_lst *l, long time, int status);

//start_simulation.c
int		start_simulation(t_data *data, t_lst *l, long num_philo);

//free_all.c
int		free_all(t_info *info, t_flags *flags, t_data *data, t_lst *l);

//save_argv.c
int		save_argv(int argc, char **argv, t_info **info);

//init_lst.c
int		init_lst(t_info *info, t_data **data, t_lst **l);

//mutex.t
void	destroy_all_mutex(t_data *data, long num_philo);
int	activate_mutex(t_data *data, long num_philo);

//utils.c
int		put_error(const char *str, int ret);
long	what_time(void);

//ft_utils.c
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_atol(const char *str);

#endif
