#include "philo.h"

void	*philo_activity(void *philo_arg)
{
	t_philo	*philo;
	long	time_start_eat;
	long	time_start_think;

	philo = (t_philo *)philo_arg;
	if ((time_start_eat = philo_gettime()) < 0)
		return (NULL);
	if ((philo->index % 2)
		usleep(200);
	while (1)
	{
		if ((time_start_eat = philo_eat(philo, time_start_eat)) < 0)
			return (NULL);
		if (philo_sleep(philo, time_start_eat) < 0)
			return (NULL);
		if ((time_start_think = philo_gettime()) < 0)
			return (NULL);
		philo_putstatus(philo->index, time_start_think, PHILO_S_THINKING);
	}
	return (NULL);
}
