#include "philo.h"

int	main(int argc, char **argv)
{
	long	i;
	long	n_philo;
	t_lst	*lst;
	pthread_t	*p;

	if (ft_save_argv(argc, argv, &lst) < 0)
		return (-1);
	printf("cool\n");
	return (0);
	(void)i;
	(void)n_philo;
	if (ft_init_pthread(&lst, &p, lst->n_philo) < 0)
		return (ft_free_all(lst, NULL, 1));
/*
	n_philo = philo[0].n_philo;
	i = 0;
	while (i < n_philo)
	{
		pthread_create(&philo_pthread[i], NULL, philo_activity, &philo[i]);
		i++;
	}
	i = 0;
	while (i < n_philo)
		pthread_join(philo_pthread[i++], NULL);
	philo_mutex_destroy(n_philo);
	return (philo_free_ret(philo, philo_pthread, 1));
*/
}
