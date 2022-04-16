#include "philo.h"

int	ft_free_all(t_thrd *th, pthread_t *p, int ret)
{
	free (p);
	free (th->fork);
	free (th->mutex_fork);
	free (th->fork_rsvd); // needed?
//	free (th);
	return (ret);
}
