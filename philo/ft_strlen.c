#include "philo.h"

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
