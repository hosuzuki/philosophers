/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 09:12:40 by hos               #+#    #+#             */
/*   Updated: 2022/09/18 14:24:34 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s++))
		i++;
	return (i);
}
