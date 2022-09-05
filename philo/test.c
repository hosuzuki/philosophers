# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>

# define INTERVAL	200

enum e_status
{
	ONE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
};

typedef struct	s_info
{
	long		num_philo;
	long		ms_die;
	long		ms_eat;
	long		ms_sleep;
	long		num_to_eat;
}	t_info;

typedef struct	s_mt
{
	int	end_flag;
	long	*forks;
	pthread_mutex_t	*mt_forks;
	pthread_mutex_t	mt_end_flag;
	pthread_mutex_t	mt_write;
} t_mt;

typedef struct	s_lst
{
	long	index;
	int	status;
	long	last_meal;
	long	eat_count;
//	int	*fork;
	t_info	*info;
	t_mt *mt;
} t_lst;

//put_status.c
void	put_status(t_lst *l, long time, int status);

//start_simulation.c
int	start_simulation(t_lst *l, long num_philo);

//free_all.c
int free_all(t_info *info, t_mt *mt, t_lst *l);

//save_argv.c
int	save_argv(int argc, char **argv, t_info **info);

//init_lst.c
int	init_lst(t_lst **l, t_info *info);

//utils.c
int	put_error(const char *str, int ret);
long	what_time(void);

//ft_utils.c
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int	ft_atol(const char *str);
int	ft_isdigit(int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
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

char	*create_str_to_put(t_lst *l, long time, int status)
{
	char	*ret;
	long	len;
	
	len = count_num_digits(time) + count_num_digits(l->index) + \
		message_len(status) + 1;
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	digit_cat(ret, time);
	ft_strlcat(ret, " ", sizeof(ret));
	digit_cat(ret, l->index);
	if (status == ONE_FORK)
		ft_strlcat(ret, " has taken a fork\n", sizeof(ret));
	else if (status == EATING)
		ft_strlcat(ret, " is eating\n", sizeof(ret));
	else if (status == SLEEPING)
		ft_strlcat(ret, " is sleeping\n", sizeof(ret));
	else if (status == THINKING)
		ft_strlcat(ret, " is thinking\n", sizeof(ret));
	else if (status == DEAD)
		ft_strlcat(ret, " died\n", sizeof(ret));
//	else
//		ft_strlcat(ret, " is in undefined status\n", sizeof(ret));
	ret[len] = '\0';
	return (ret);
}

void	put_status(t_lst *l, long time, int status)
{
	char *ret;

	ret = create_str_to_put(l, time, status);
	if (!ret)
		return ;
	pthread_mutex_lock(&(l->mt->mt_write));
	write(1, ret, ft_strlen(ret));
	pthread_mutex_unlock(&(l->mt->mt_write));
	free (ret);
}

int		ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int		ft_isspace(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

int			ft_atol(const char *str)
{
	long			sign;
	unsigned long	abs;

	sign = 1;
	abs = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		abs = abs * 10 + *(str++) - '0';
	return (sign * (long)abs);
}

size_t		ft_strlen(const char *s)
{
	size_t count;

	count = 0;
	while (*(s++))
		count++;
	return (count);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	int		flag_reach_dstsize;

	if (dstsize > 0)
		flag_reach_dstsize = 0;
	else
		flag_reach_dstsize = 1;
	i = 0;
	while (src[i] != '\0')
	{
		if (i == dstsize - 1)
		{
			dst[dstsize - 1] = '\0';
			flag_reach_dstsize = 1;
		}
		if (flag_reach_dstsize == 0)
			dst[i] = src[i];
		i++;
	}
	if (flag_reach_dstsize == 0)
		dst[i] = '\0';
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	if (dst[i] == '\0' && i != dstsize)
		return (ft_strlcpy(dst + i, src, dstsize - i) + i);
	return (i + ft_strlen(src));
}

int free_all(t_info *info, t_mt *mt, t_lst *l)
{
	if (info)
		free (info);
	if (mt)
	{
		free(mt->forks);
		free(mt->mt_forks);
		free (mt);
	}
	if (l)
		free (l);
	return (-1);
}

static int	isnumber(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

static int	error_checker(int argc, char **argv)
{
	int	i;
	long	num_philo;
	long	num_to_eat;
	
	if (argc != 5 && argc != 6)
		return (put_error("Invalid Argument", -1));
	i = 1;
	while (argv[i])
	{
		if (!isnumber(argv[i++]))
			return (put_error("Invalid Argument", -1));
	}
	num_philo = ft_atol(argv[1]);
	if (num_philo < 2)
		return (put_error("Invalid Argument", -1));
	if (argc == 6)
	{
		num_to_eat = ft_atol(argv[5]);
		if (num_to_eat < 1)
			return (put_error("Invalid Argument", -1));
	}
	return (0);
}

int	save_argv(int argc, char **argv, t_info **info)
{
	if (error_checker(argc, argv) < 0)
		return (-1);
	*info = (t_info *)malloc(sizeof(t_info));
	if (!*info)
		return (-1);
	(*info)->num_philo = ft_atol(argv[1]);
	(*info)->ms_die = ft_atol(argv[2]);
	(*info)->ms_eat = ft_atol(argv[3]);
	(*info)->ms_sleep = ft_atol(argv[4]);
	if (argc == 6)
		(*info)->num_to_eat = ft_atol(argv[5]);
	else
		(*info)->num_to_eat = -1;
	return (0);
}

static void	destroy_all_mutex(t_lst *l, long num_philo)
{
	long	i;

	pthread_mutex_destroy(&(l->mt->mt_end_flag));
	pthread_mutex_destroy(&(l->mt->mt_write));
	i = 0;
	while (i < num_philo)
		pthread_mutex_destroy(&(l->mt->mt_forks[i++]));
}

void	*life_of_philo(void *arg) 
{
	t_lst	*l;
	long	time_eat;
	long	time_think;

	l = (t_lst *)arg;
	if (l->index % 2)
		usleep (200);
	if ((time_eat = what_time()) < 0)
		return (NULL);
	while (1)
	{
//		if ((time_eat = eat_task(l, time_eat)) < 0)
//			return (NULL);
//		if (sleep_task(lst, time_eat) < 0)
//			return (NULL);
		if ((time_think = what_time()) < 0)
			return (NULL);
		put_status(l, time_think, THINKING);
		if (l->index++ > l->info->num_philo)
			break ;
	}
	return (NULL);
}

int	start_simulation(t_lst *l, long num_philo)
{
	long	i;
	pthread_t *philos;

	philos = (pthread_t *)malloc(sizeof(pthread_t) * num_philo);
	if (!philos)
		return (free_all(l->info, l->mt, l));
	i = 0;
	while (i < num_philo)
	{
		pthread_create(&philos[i], NULL, life_of_philo, &l[i]);
		i++;
	}
	i = 0;
	while (i < num_philo)
		pthread_join(philos[i++], NULL);
	destroy_all_mutex(l, num_philo);
	return(0);
}

long	what_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (-1);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	put_error(const char *str, int ret)
{
	printf("ERROR: %s\n", str);
	return (ret);
}

int	main(int argc, char **argv)
{
//	long	n_philo;
	//pthread_t	*p;
	t_info	*info;
	t_lst	*l;

	if (save_argv(argc, argv, &info) < 0)
		return (-1);
/*	printf("info->num_philo: %ld\n", info->num_philo);
	printf("info->ms_die: %ld\n", info->ms_die);
	printf("info->ms_eat: %ld\n", info->ms_eat);
	printf("info->ms_sleep: %ld\n", info->ms_sleep);
	printf("info->num_to_eat: %ld\n", info->num_to_eat);
*/	
	if (init_lst(&l, info) < 0)
		return (-1);
/*	printf("l[0].index: %ld\n", l[0].index);
	printf("l[1].index: %ld\n", l[1].index);
	printf("l[0]->mt.end_flag: %d\n", l[0].mt->end_flag);
	printf("l[1]->mt.end_flag: %d\n", l[1].mt->end_flag);
*/
	if (start_simulation(l, l->info->num_philo) < 0)
 		return (-1);
	free_all(info, l->mt, l);
	return (0);
}
