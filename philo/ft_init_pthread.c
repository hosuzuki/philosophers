#include "philo.h"

static int	ft_init_mutex_fork(t_thrd *th, long n_philo)
{
	long	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&th->mutex_fork[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&th->mutex_fork[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	ft_init_mutex(t_thrd *th, long n_philo)
{
	if (pthread_mutex_init(&th->mutex_flgend, NULL))
		return (-1);
	if (pthread_mutex_init(&th->mutex_n_finished, NULL))
	{
		pthread_mutex_destroy(&th->mutex_flgend);
		return (-1);
	}
	if (pthread_mutex_init(&th->mutex_write, NULL))
	{
		pthread_mutex_destroy(&th->mutex_flgend);
		pthread_mutex_destroy(&th->mutex_n_finished);
		return (-1);
	}
	if (ft_init_mutex_fork(th, n_philo))
	{
		pthread_mutex_destroy(&th->mutex_flgend);
		pthread_mutex_destroy(&th->mutex_n_finished);
		pthread_mutex_destroy(&th->mutex_write);
		return (-1);
	}
	return (0);
}

int	ft_init_pthread(t_thrd *th, pthread_t **p, long n_philo)
{
	int	i;

	*p = (pthread_t *)malloc(sizeof(pthread_t) * n_philo);
	if (!(*p))
		return (-1);
	th->flgend = 0;
	th->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_philo);
	th->fork = (int *)malloc(sizeof(int) * n_philo);
	th->fork_rsvd = (int *)malloc(sizeof(int) * n_philo);
	if (!th->mutex_fork || !th->fork || !th->fork_rsvd)
		return (-1);
	i = 0;
	while (i < n_philo)
	{
		th->fork[i] = 0;
		th->fork_rsvd[i] = -1;
		i++;
	}
	printf("ft_init_pthread\n");
	if (ft_init_mutex(th, n_philo) < 0)
		return (-1);
	return (0);
}
