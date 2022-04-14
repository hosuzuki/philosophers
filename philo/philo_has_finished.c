#include "philo.h"

int	philo_has_finished(long time_start, long time_to_do)
{
	long time_now;

	if ((time_now = philo_gettime()) < 0)
		return (1);
	if (time_now - time_start >= time_to_do)
		return (1);
	return (0);
}
