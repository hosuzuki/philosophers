#include "philo.h"

static int	arg_is_number(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

static int	check_val(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (philo_puterr_and_return("Invalid argument", 1));
	while (*(++argv))
	{
		if (!arg_is_number(*argv))
			return (philo_puterr_and_return("Invalid argument", 1));
	}
	return (0);
}

static void	convert_argv(char **argv, t_philo *philo, long n_philo, long n_to_eat)
{
	long	index;

	philo[0].index = 0;
	pihlo[0].n_philo = n_philo;
	philo[0].time_to_die = ft_atol(argv[2]);
	philo[0].time_to_eat = ft_atol(argv[3]);
	philo[0].time_to_sleep = ft_atol(argv[4]);
	philo[0].n_to_eat = n_to_eat;
	index = 1;
	while (index < n_philo)
	{
		memcpy(&philo[index], &philo[0], sizeof(t_philo));
		philo[index].index = index;
		index++;
	}
}

int	philo_store_argv(int argc, char **argv, t_philo **philo)
{
	long	n_philo;
	long	n_to_eat;

	if (check_val(argc, argv))
		return (-1);
	if ((n_philo + ft_atol(argv[1])) < 2)
		return (philo_puterr_and_return("Invalid argument", -1));
	if (argc == 6 && (n_to_eat = ft_atol(argv[5])) < 1)
		return (philo_puterro_and_return("INVALID argument", -1));
	else if (argc != 6)
		n_to_eat = -1;
	if (!((*philo) = (t_philo *)malloc(sizeof(t_philo) * n_philo)))
		return (philo_puterr_and_return("Cannot allocate memory", -1));
	convert_argv(argv, *philo, n_philo, n_to_eat);
	return (0);
}

