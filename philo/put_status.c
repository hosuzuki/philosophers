/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/05 09:13:18 by hos              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_digit(long num)
{
	int	digit;

	digit = (num < 0) ? 2 : 1;
	while (num >= 10L)
	{
		num /= 10L;
		digit++;
	}
	return (digit);
}

static void	cat_number(char *buf, long num)
{
	int	digit;

	while (*buf)
		buf++;
	digit = get_digit(num);
	buf[digit] = '\0';
	while (digit > 0)
	{
		buf[digit - 1 ] = (char)(num % 10L) + '0';
		num /= 10;
		digit--;
	}
}

void	put_status(t_lst *l, long time, int status)
{
	char	buf[256];

	buf[0] = '\0';
	cat_number(buf, time);
	ft_strlcat(buf, " ", sizeof(buf));
	cat_number(buf, l->index + 1);
	if (status == ONE_FORK)
		ft_strlcat(buf, " has taken a fork\n", sizeof(buf));
	else if (status == EATING)
		ft_strlcat(buf, " is eating\n", sizeof(buf));
	else if (status == SLEEPING)
		ft_strlcat(buf, " is sleepgin\n", sizeof(buf));
	else if (status == THINKING)
		ft_strlcat(buf, " is thinking\n", sizeof(buf));
	else if (status == DEAD)
		ft_strlcat(buf, " died\n", sizeof(buf));
	else
		ft_strlcat(buf, " is in undefined status\n", sizeof(buf));
	pthread_mutex_lock(&(l->mt->mt_write));
	write(1, buf, ft_strlen(buf));
	pthread_mutex_unlock(&(l->mt->mt_write));
}
