#include "philo.h"

static int	ft_init_mutex_fork(long n_philo)
{
	long	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&lst->mutex_fork[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&lst->mutex_fork[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	ft_init_mutex(t_lst **lst, long n_philo)
{
	if (pthread_mutex_init(&lst->mutex_flgend, NULL))
		return (-1);
	if (pthread_mutex_init(&lst->mutex_n_finished, NULL))
	{
		pthread_mutex_destroy(&lst->mutex_flgend);
		return (-1);
	}
	if (pthread_mutex_init(&lst->mutex_write, NULL))
	{
		pthread_mutex_destroy(&lst->mutex_flgend);
		pthread_mutex_destroy(&lst->mutex_n_finished);
		return (-1);
	}
	if (ft_init_mutex_fork(n_philo))
	{
		pthread_mutex_destroy(&lst->mutex_flgend);
		pthread_mutex_destroy(&lst->mutex_n_finished);
		pthread_mutex_destroy(&lst->mutex_write);
		return (-1);
	}
	return (0);
}

int	ft_init_pthread(t_lst **lst, pthread_t **p, long n_philo)
{
	int	i;

	*p = (pthread_t *)malloc(sizeof(pthread_t) * n_philo);
	if (!(*p))
		return (-1);
	lst->flgend = 0;
	lst->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_philo);
	lst->fork = (int *)malloc(sizeof(int) * n_philo);
	lst->fork_rsvd = (int *)malloc(sizeof(int) * n_philo);
	if (!lst->mutex_fork || !lst->fork || lst->fork_rsvd)
		return (-1);
	i = 0;
	while (i < n_philo)
	{
		lst->fork[i] = 0;
		lst->fork_rsvd[i] = -1;
		i++;
	}
	if (ft_init_mutex(lst, n_philo) < 0)
		return (-1);
	return (0);
}
