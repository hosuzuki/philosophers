#include "philo.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	if (dst[i] != '\0' && i != dstsize)
		return (ft_strlcpy(dst + i, src, dstsize - i) + i);
	return (i + ft_strlen(src));
}
