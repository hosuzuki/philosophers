/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/02 13:41:06 by hos              ###   ########.fr       */
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

static int	error_checker(int argc, char **argv)
{
	int	i;
	long	num_philo;
	long	num_to_eat;
	
	if (argc != 5 && argc != 6)
		return (put_error("Invalid Argument", -1));
	i = 1;
	while (argv[i])
	{
		if (!isnumber(argv[i++]))
			return (put_error("Invalid Argument", -1));
	}
	num_philo = ft_atol(argv[1]);
	if (num_philo < 2)
		return (put_error("Invalid Argument", -1));
	if (argc == 6)
	{
		num_to_eat = ft_atol(argv[5]);
		if (num_to_eat < 1)
			return (put_error("Invalid Argument", -1));
	}
	return (0);
}

int	save_argv(int argc, char **argv, t_info **info)
{
	if (error_checker(argc, argv) < 0)
		return (-1);
	*info = (t_info *)malloc(sizeof(t_info));
	if (!*info)
		return (-1);
	(*info)->num_philo = ft_atol(argv[1]);
	(*info)->ms_die = ft_atol(argv[2]);
	(*info)->ms_eat = ft_atol(argv[3]);
	(*info)->ms_sleep = ft_atol(argv[4]);
	if (argc == 6)
		(*info)->num_to_eat = ft_atol(argv[5]);
	else
		(*info)->num_to_eat = -1;
	return (0);
}
/*
int	save_argv(int argc, char **argv, t_info **info)
{
	t_info *new;
	
	if (error_checker(argc, argv) < 0)
		return (-1);
	new = (t_info *)malloc(sizeof(t_info));
	if (!new)
		return (-1);
	new->num_philo = ft_atol(argv[1]);
	new->ms_die = ft_atol(argv[2]);
	new->ms_eat = ft_atol(argv[3]);
	new->ms_sleep = ft_atol(argv[4]);
	if (argc == 6)
		new->num_to_eat = ft_atol(argv[5]);
	else
		new->num_to_eat = -1;
	*info = new;
	return (0);
}*/
