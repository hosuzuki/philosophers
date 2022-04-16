#include "philo.h"

long	ft_return_time(void)
{
	long	res;
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (-1);
	res = t.tv_sec * 1000;
	res += t.tv_usec / 1000;
	return (res);
}
