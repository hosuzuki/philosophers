#ifndef PHILO_H
# define PHILO_H

#	include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# include <string.h>

# define PHILO_WHILE_INTERVAL_USEC	200
# define PHILO_S_TAKENFORK			1
# define PHILO_S_EATING				2
# define PHILO_S_SLEEPING			3
# define PHILO_S_THINKING			4
# define PHILO_S_DEAD				5

typedef struct	s_philo
{
	long		index;
	long		n_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		n_to_eat;
}				t_philo;

int				*g_fork;
int				*g_fork_rsvd_by;
pthread_mutex_t	*g_mutex_fork;
int				g_flgend;
pthread_mutex_t	g_mutex_flgend;
int				g_n_finished;
pthread_mutex_t	g_mutex_n_finished;
pthread_mutex_t	g_mutex_write;

int				philo_init(pthread_t **philo_pthread, long n_philo);
void			*philo_activity(void *philo_arg);
long			philo_eat(t_philo *philo, long time_start_eating);
int				philo_sleep(t_philo *philo, long time_start_eating);
int				philo_check_dead(t_philo *philo, long time_start_eating);
int				philo_free_ret(t_philo *philo, pthread_t *philo_pthread,
																	int ret);
void			philo_mutex_destroy(long n_philo);
int				philo_store_argv(int argc, char **argv, t_philo **philo);
long			philo_gettime(void);
void			philo_putstatus(long philo_index, long time_ms,
														int philo_status);
int				philo_has_finished(long time_start, long time_to_do);
int				philo_puterr_and_return(const char *str, int ret);

int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_atol(const char *str);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);

#endif
