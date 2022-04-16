#include "philo.h"

void	*ft_activation(void *philo_arg)
{
	t_lst	*lst;
	long	start_to_eat;
//	long	start_to_think;

	lst = (t_lst *)philo_arg;
	if ((start_to_eat = ft_return_time()) < 0)
		return (NULL);
	if (lst->index % 2)
		usleep (200);
/*
	while (1)
	{
		if ((start_to_eat = ft_eat(lst, start_to_eat)) < 0)
			return (NULL);
		if (ft_sleep(lst, start_to_eat) < 0)
			return (NULL);
		if ((start_to_think = ft_return_time()) < 0)
			return (NULL);
		ft_put_status(lst->index, start_to_think, PHILO_S_THINKING);
	}
*/
	return (NULL);
}
