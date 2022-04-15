#include "philo.h"

static int	ft_isnumber(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

static int	ft_init_lst(char **argv, t_lst *lst, long n_philo, long n_to_eat)
{
	long	i;

	if (!(lst = (t_lst *)malloc(sizeof(t_lst) * n_philo)))
		return (ft_put_error("Malloc Error", -1));
	lst[0].index = 0;
	lst[0].n_philo = n_philo;
	lst[0].time_to_die = ft_atol(argv[2]);
	lst[0].time_to_eat = ft_atol(argv[3]);
	lst[0].time_to_sleep = ft_atol(argv[4]);
	lst[0].n_to_eat = n_to_eat;
	i = 1;
	while (i < n_philo) // why ??
	{
		ft_memcpy(&lst[i], &lst[0], sizeof(t_lst));
		lst[i].index = i;
		i++;
	}
	return (0);
}

int	ft_save_argv(int argc, char **argv, t_lst **lst)
{
	long	n_philo;
	long	n_to_eat;
	int i;
	
	if (argc != 5 && argc != 6)
		return (ft_put_error("Invalid Argument", -1));
	i = 1;
	while (argv[i])// could be i <= argc
		if (!ft_isnumber(argv[i++]))
			return (ft_put_error("Invalid Argument", -1));
	n_philo = ft_atol(argv[1]);
	if (n_philo  < 2)
		return (ft_put_error("Invalid Argument", -1));
	if (argc == 6)
	{
		n_to_eat = ft_atol(argv[5]);
		if (n_to_eat < 1)
			return (ft_put_error("Invalid Argument", -1));
	}
	else
		n_to_eat = -1;
	if (ft_init_lst(argv, *lst, n_philo, n_to_eat) < 0)
		return (-1);
	return (0);
}

