/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/19 21:16:45 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <semaphore.h>

# define SEM_FORKS "/forks"
# define SEM_WRITER "/writer"
# define SEM_MEAL_FLAG "/meal_flag"
# define INTERVAL 500

typedef struct s_info
{
	long	num_philo;
	long	ms_die;
	long	ms_eat;
	long	ms_sleep;
	long	num_to_eat;
}	t_info;

typedef struct s_sem
{
	sem_t	*forks;
	sem_t	*writer;
//	sem_t	**meal_flags;
}	t_sem;

typedef struct s_lst
{
	long	index;
	long	last_meal;
//	long	eat_count;
	sem_t	*meal_flag;
	t_info	*info;
	t_sem	*sem;
}	t_lst;

//sleep_task.c
int		sleep_task(t_lst *l);

//death_watcher.c
void	activate_death_watcher(t_lst *l);

//eat_task.c
long	eat_task(t_lst *l);

//start_simulation.c
int		start_simulation(t_lst *l, long num_philo);

//save_argv.c
int		save_argv(int argc, char **argv, t_info **info);

//init_lst.c
int		init_lst(t_lst **l, t_info *info);

//utils.c
void	put_error_and_exit(const char *str, int ret);
long	what_time(void);
int		free_all(t_info *info, t_sem *sem, t_lst *l);
bool	task_is_finished(long time_start, long duration);

//ft_utils.c
int		ft_isdigit(int c);
int		ft_atol(const char *str);

#endif
