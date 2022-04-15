#include "philo.h"

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
