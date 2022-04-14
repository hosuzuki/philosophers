#include "philo.h"

static int	mutex_fork_init(long n_philo)
{
	long	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&g_mutex_fork[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&g_mutex_fork[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	mutex_init(long n_philo)
{
	if (pthread_mutex_init(&g_mutex_flgend, NULL))
		return (-1);
	if (pthread_mutex_init(&g_mutex_n_finished, NULL))
	{
		pthread_mutex_destroy(&g_mutex_flgend);
		return (-1);
	}
	if (pthread_mutex_init(&g_mutex_write, NULL))
	{
		pthread_mutex_destroy(&g_mutex_flgend);
		pthread_mutex_destroy(&g_mutex_n_finished);
		return (-1);
	}
	if (mutex_fork_init(n_philo))
	{
		pthread_mutex_destroy(&g_mutex_flgend);
		pthread_mutex_destroy(&g_mutex_n_finished);
		pthread_mutex_destroy(&g_mutex_write);
		return (-1);
	}
	return (0);
}

int	philo_init(pthread_t **philo_pthread, long n_philo)
{
	int	i;

	*philo_pthread = (pthread_t *)malloc(sizeof(pthread_t) * n_philo);
	if (!(*philo_pthread))
		return (-1);
	g_flgend = 0;
	g_mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_philo);
	if (!g_mutex_fork)
		return (-1);
	if (!(g_fork = (int *)malloc(sizeof(int) * n_philo)))
		return (-1);
	if (!(g_fork_rsvd_by = (int *)malloc(sizeof(int) * n_philo)))
		return (-1);
	i = 0;
	while (i < n_philo)
	{
		g_fork[i] = 0;
		g_fork_rsvd_by[i] = -1;
		i++;
	}
	if (mutex_init(n_philo) < 0)
		return (-1);
	return (0);
}
