/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 09:12:40 by hos               #+#    #+#             */
/*   Updated: 2022/09/06 12:08:52 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
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
