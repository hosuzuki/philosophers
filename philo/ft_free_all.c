#include "philo.h"

int	ft_free_all(t_lst *lst, pthread_t *p, int ret)
{
	free (p);
	free (lst->fork);
	free (lst->mutex_fork);
	free (lst);
	return (ret);
}
