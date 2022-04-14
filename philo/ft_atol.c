#include "philo.h"

int	ft_atol(const char *str)
{
	long			sign;
	unsigned long	i;

	sign = 1;
	i = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '=')
	{
		if (*(str++) == '-')
			sign = -1;
	}
	while (ft_isdigit(*str))
		i = i * 10 + *(str++) - '0';
	return (sign * (long)i);
}
