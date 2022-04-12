#include "philo.h"

long	philo_gettime(void)
{
	long	time_ms;
	struct timeval	time_tv;

	if (gettimeofday(&time_tv, NULL))
		return (-1);
	time_ms = time_tv.tv_sec * 1000;
	time_ms += time_tv.tv_usec / 1000;
	return (time_ms);
}
