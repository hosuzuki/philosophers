#include "philo.h"

void	philo_mutex_destroy(long n_philo)
{
	long	i;

	pthread_mutex_destroy(&g_mutex_flgend);
	pthread_mutex_destroy(&g_mutex_n_finished);
	pthread_mutex_destroy(&g_mutex_write);
	i = 0;
	while (i < n_philo)
		pthread_mutex_destroy(&g_mutex_fork[i++]);
}
