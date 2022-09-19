#include "philo.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(src);
	if (dstsize == 0)
		return (s_len);
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (s_len);
}

static size_t	dst_length(char *dst, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i < dstsize)
	{
		if (!dst[i])
			break ;
		i++;
	}
	return (i);
}

static size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len1;
	size_t	len2;

	len1 = dst_length(dst, dstsize);
	len2 = ft_strlen(src);
	if (dstsize == 0)
		return (len2);
	if (dstsize <= len1)
		return (len2 + dstsize);
	if (dstsize > len1 + len2)
		ft_strlcpy(dst + len1, src, len2 + 1);
	else
		ft_strlcpy(dst + len1, src, dstsize - len1);
	return (len1 + len2);
}

static char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dst;

	i = ft_strlen(s1);
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, i + 1);
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	size_t	len1;
	size_t	len2;

	d = NULL;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	d = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!d)
		return (NULL);
	ft_strlcpy(d, s1, len1 + 1);
	ft_strlcat(d, s2, len1 + len2 + 1);
	return (d);
}
