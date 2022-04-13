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

static
