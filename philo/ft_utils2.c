/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:56:38 by hos               #+#    #+#             */
/*   Updated: 2022/09/10 18:34:30 by hos              ###   ########.fr       */
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

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*dest;

	i = 0;
	dest = (unsigned char *)b;
	while (i < len)
		dest[i++] = (unsigned char)c;
	return (b);
}

static bool	check_bytes(size_t *sum, size_t *count, size_t *size)
{
	if (*count == 0 || *size == 0)
	{
		*count = 1;
		*size = 1;
	}
	*sum = *count * *size;
	if (*sum / *count != *size)
		return (false);
	return (true);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;
	size_t	sum;

	errno = 0;
	if (!check_bytes(&sum, &count, &size))
	{
		errno = ENOMEM;
		return (NULL);
	}
	res = malloc(sum);
	if (!res)
		return (NULL);
	ft_memset(res, 0, sum);
	return (res);
}
