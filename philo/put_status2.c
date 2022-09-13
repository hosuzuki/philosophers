/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:36:42 by hos               #+#    #+#             */
/*   Updated: 2022/09/11 15:14:02 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	count_num_digits(long num)
{
	int	digit;

	if (num < 0)
		digit = 2;
	else
		digit = 1;
	while (num >= 10L)
	{
		num /= 10L;
		digit++;
	}
	return (digit);
}

static void	digit_cat(char *ret, long time, int first_time)
{
	int	digit;

	if (first_time != 1)
	{
		while (*ret)
			ret++;
	}
	digit = count_num_digits(time);
	ret[digit] = '\0';
	while (digit > 0)
	{
		ret[digit - 1] = (char)(time % 10L) + '0';
		time /= 10;
		digit--;
	}
}

static int	message_len(int status)
{
	if (status == ONE_FORK)
		return (18);
	else if (status == EATING)
		return (11);
	else if (status == SLEEPING)
		return (13);
	else if (status == THINKING)
		return (13);
	else if (status == DEAD)
		return (6);
	return (0);
}

static void	put_message(char *ret, int status, long len)
{
	if (status == ONE_FORK)
		ft_strlcat(ret, " has taken a fork\n", len + 1);
	else if (status == EATING)
		ft_strlcat(ret, " is eating\n", len + 1);
	else if (status == SLEEPING)
		ft_strlcat(ret, " is sleeping\n", len + 1);
	else if (status == THINKING)
		ft_strlcat(ret, " is thinking\n", len + 1);
	else if (status == DEAD)
		ft_strlcat(ret, " died\n", len + 1);
	return ;
}

char	*create_str_to_put(t_lst *l, long time, int status)
{
	char	*ret;
	long	len;

	len = count_num_digits(time) + count_num_digits(l->index) + \
		message_len(status) + 1;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	digit_cat(ret, time, 1);
	ft_strlcat(ret, " ", len + 1);
	digit_cat(ret, l->index, 2);
	put_message(ret, status, len);
	ret[len] = '\0';
	return (ret);
}
