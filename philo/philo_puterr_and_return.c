#include "philo.h"

int	philo_puterr_and_return(const char *str, int ret)
{
	char	buf[256];

	ft_strlcpy(buf, "Philosophers: ", sizeof(buf));
	ft_strlcat(buf, str, sizeof(buf));
	ft_strlcat(buf, "\n", sizeof(buf));
	write(1, buf, ft_strlen(buf));
	return (ret);
}
