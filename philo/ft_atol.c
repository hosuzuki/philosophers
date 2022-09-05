/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:02 by hos               #+#    #+#             */
/*   Updated: 2022/09/05 09:07:01 by hos              ###   ########.fr       */
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
	unsigned long	res;
	int i;

	sign = 1;
	res = 0;
	i = 0;
	if (!str)
	 return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
		res = res * 10 + str[i++] - '0';
	return (sign * (long)res);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while(*(s++))
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	int		flag;

	if (!src)
		return (-1);
	if (dstsize > 0)
		flag = 0;
	else
		flag = 1;
	i = 0;
	while (src[i] != '\0')
	{
		if (i == dstsize - 1)
		{
			dst[i] = '\0';
			flag = 1;
		}
		if (flag == 0)
			dst[i] = src[i];
		i++;
	}
	if (flag == 0)
		dst[i] = '\0';
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	if (dst[i] != '\0' && i != dstsize)
		return (ft_strlcpy(dst + i, src, dstsize - i) + i);
	return (i + ft_strlen(src));
}


