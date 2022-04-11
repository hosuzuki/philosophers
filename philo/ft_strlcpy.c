size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	int		flag;

	if (!src)
		return (-1);
	if (dstsize > 0)
		flag = 0;
	else
		flag = 1;
	i = 0;
	while (src[i] != '\0')
	{
		if (i == dstsize - 1)
		{
			dst[i] = '\0';
			flag = 1;
		}
		if (flag == 0)
			dst[i] = src[i];
		i++;
	}
	if (flag == 0)
		dst[i] = '\0';
	return (i);
}
