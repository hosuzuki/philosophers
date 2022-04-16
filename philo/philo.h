#ifndef PHILO_H
# define PHILO_H

#	include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>

# define PHILO_WHILE_INTERVAL_USEC	200
# define PHILO_S_TAKENFORK			1
# define PHILO_S_EATING				2
# define PHILO_S_SLEEPING			3
# define PHILO_S_THINKING			4
# define PHILO_S_DEAD				5

typedef struct	s_lst
{
	long		index;
	long		n_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		n_to_eat;
}	t_lst;

typedef struct	s_thrd
{
	int				flgend;
	pthread_mutex_t	*mutex_fork;
	int				*fork;
	int				*fork_rsvd;
	pthread_mutex_t	mutex_flgend;
	pthread_mutex_t	mutex_n_finished;
	pthread_mutex_t	mutex_write;
	int				n_finished;
} t_thrd;

int	ft_init_pthread(t_thrd *th, pthread_t **p, long n_philo);
void	*ft_activation(void *philo_arg);
long	ft_return_time(void);
int	ft_free_all(t_thrd *th, pthread_t *p, int ret);
int				ft_save_argv(int argc, char **argv, t_lst **lst);
int	ft_put_error(const char *str, int ret);

long			philo_eat(t_lst *lst, long time_start_eating);
int				philo_sleep(t_lst *lst, long time_start_eating);
int				philo_check_dead(t_lst *lst, long time_start_eating);
void			philo_mutex_destroy(long n_philo);
void			philo_putstatus(long philo_index, long time_ms,
														int philo_status);
int				philo_has_finished(long time_start, long time_to_do);

void	*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_atol(const char *str);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);

#endif
