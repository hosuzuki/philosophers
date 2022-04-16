#include "philo.h"

int	main(int argc, char **argv)
{
	long	i;
	long	n_philo;
	t_lst	*lst;
	pthread_t	*p;
	t_thrd	th;

	if (ft_save_argv(argc, argv, &lst) < 0)
		return (-1);
	(void)i;
	(void)n_philo;
	if (ft_init_pthread(&th, &p, lst->n_philo) < 0)
		return (ft_free_all(&th, NULL, 1));
	i = 0;
	while (i < lst[0].n_philo)
	{
		pthread_create(&p[i], NULL, ft_activation, &lst[i]);
		i++;
	}
	printf("cool\n");
	return (0);
/*
	i = 0;
	while (i < n_philo)
		pthread_join(philo_pthread[i++], NULL);
	philo_mutex_destroy(n_philo);
	return (philo_free_ret(philo, philo_pthread, 1));
*/
}
