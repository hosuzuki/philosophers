/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:56:38 by hos               #+#    #+#             */
/*   Updated: 2022/09/14 22:43:34 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_isspace(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

int	ft_atol(const char *str)
{
	long			sign;
	unsigned long	abs;

	sign = 1;
	abs = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign = -1;
	while (ft_isdigit(*str))
		abs = (abs * 10) + (*(str++) - '0');
	return (sign * (long)abs);
}
