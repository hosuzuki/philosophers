#include "philo.h"

int	philo_free_ret(t_philo *philo, pthread_t *philo_pthread, int ret)
{
	free (philo);
	free (philo_pthread);
	free (g_fork);
	free (g_mutex_fork);
	return (ret);
}
