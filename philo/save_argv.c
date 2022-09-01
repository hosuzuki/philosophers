/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/08/31 22:36:52 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	isnumber(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

static int	init_lst(char **argv, t_lst **lst, long n_philo, long n_to_eat)
{
	long	i;

	if (!(*lst = (t_lst *)malloc(sizeof(t_lst) * n_philo)))
		return (put_error("Malloc Error", -1));
	lst[0]->index = 0;
	lst[0]->n_philo = n_philo;
	lst[0]->die = ft_atol(argv[2]);
	lst[0]->eat = ft_atol(argv[3]);
	lst[0]->sleep = ft_atol(argv[4]);
	lst[0]->n_eat = n_to_eat;
	i = 1;
	while (i < n_philo) // why ??
	{
		ft_memcpy(&lst[i], &lst[0], sizeof(t_lst));
		lst[i]->index = i;
		i++;
	}
	return (0);
}

int	save_argv(int argc, char **argv, t_lst **lst)
{
	long	n_philo;
	long	n_to_eat;
	int i;
	
	if (argc != 5 && argc != 6)
		return (put_error("Invalid Argument", -1));
	i = 1;
	while (argv[i])
		if (!isnumber(argv[i++]))
			return (put_error("Invalid Argument", -1));
	n_philo = ft_atol(argv[1]);
	if (n_philo < 2)
		return (put_error("Invalid Argument", -1));
	if (argc == 6)
	{
		n_to_eat = ft_atol(argv[5]);
		if (n_to_eat < 1)
			return (put_error("Invalid Argument", -1));
	}
	else
		n_to_eat = -1; // could be 0?
	if (init_lst(argv, lst, n_philo, n_to_eat) < 0)
		return (-1);
	return (0);
}
