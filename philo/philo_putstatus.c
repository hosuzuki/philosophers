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



