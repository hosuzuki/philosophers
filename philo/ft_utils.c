/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 09:12:40 by hos               #+#    #+#             */
/*   Updated: 2022/09/05 13:17:38 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int		ft_isspace(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

int			ft_atol(const char *str)
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

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*(s++))
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(src);
	if (dstsize == 0)
		return (s_len);
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (s_len);
}


/*

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	int		flag_reach_dstsize;

	if (dstsize > 0)
		flag_reach_dstsize = 0;
	else
		flag_reach_dstsize = 1;
	i = 0;
	while (src[i] != '\0')
	{
		if (i == dstsize - 1)
		{
			dst[dstsize - 1] = '\0';
			flag_reach_dstsize = 1;
		}
		if (flag_reach_dstsize == 0)
			dst[i] = src[i];
		i++;
	}
	if (flag_reach_dstsize == 0)
		dst[i] = '\0';
	return (i);
}
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	if (dst[i] == '\0' && i != dstsize)
		return (ft_strlcpy(dst + i, src, dstsize - i) + i);
	return (i + ft_strlen(src));
}
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_d;
	size_t	len_s;

	len_d = 0;
	while (len_d < dstsize)
	{
		if (!dst[len_d])
			break ;
		len_d++;
	}
	len_s = ft_strlen(src);
	if (dstsize == 0)
		return (len_s);
	if (dstsize <= len_d)
		return (len_s + dstsize);
	if (dstsize > len_d + len_s)
		ft_strlcpy(dst + len_d, src, len_s + 1);
	else
		ft_strlcpy(dst + len_d, src, dstsize - len_d);
	return (len_d + len_s);
}
