/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:39:03 by hos               #+#    #+#             */
/*   Updated: 2022/09/05 22:06:08 by hos              ###   ########.fr       */
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

static void	digit_cat(char *ret, long num)
{
	int	digit;

	while (*ret)
		ret++;
	digit = count_num_digits(num);
	ret[digit] = '\0';
	while (digit > 0)
	{
		ret[digit - 1] = (char)(num % 10L) + '0';
		num /= 10;
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
//	else
//		ft_strlcat(ret, " is in undefined status\n", sizeof(ret));
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
	digit_cat(ret, time);
	ft_strlcat(ret, " ", len + 1);
	digit_cat(ret, l->index);
	put_message(ret, status, len);
	ret[len] = '\0';
//	dprintf(STDERR_FILENO, ret);
	return (ret);
}

void update_status(t_lst *l, long time, int status)
{
	(void)time;
	if (status == EATING)
	{
//		l->last_meal = time;
		l->eat_count++;
	}
	else if (status == ONE_FORK)
		l->status = ONE_FORK;
	else if (status == SLEEPING)
		l->status = SLEEPING;
	else if (status == THINKING)
		l->status = THINKING;
	else if (status == DEAD)
		l->status = DEAD;
	return ;
}

int	put_status(t_lst *l, long time, int status)
{
	char	*ret;

	ret = create_str_to_put(l, time, status);
	if (!ret || l->mt->end_flag == 1)
		return (-1);
	pthread_mutex_lock(&(l->mt->mt_write));
	write(1, ret, ft_strlen(ret));
	pthread_mutex_unlock(&(l->mt->mt_write));
	update_status(l, time, status);
	free (ret);
	return (0);
}
