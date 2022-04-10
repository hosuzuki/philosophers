CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror
NAME		:=	philo
SRCS		:=	main.c \
				philo_store_argv.c \
				philo_has_finished.c \
				philo_putstatus.c \
				philo_puterr_and_return.c \
				ft_atol.c \
				ft_isdigit.c \
				ft_isspace.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				philo_init.c \
				philo_activity.c \
				philo_eat.c \
				philo_sleep.c \
				philo_check_dead.c \
				philo_mutex_destroy.c \
				philo_free_ret.c \
				philo_gettime.c
OBJS		:=	$(SRCS:%.c=%.o)
HEADERS		:=	philo.h \
				philo_utils.h
HEADERDIR	:=	.

.SUFFIXES: .o .c

all : $(NAME)

$(NAME) :	$(OBJS) $(HEADER)
				$(CC) $(OBJS) $(addprefix -I,$(HEADERDIR)) -o $(NAME)

.c.o :
	$(CC) $(CFLAGS) -I$(HEADERDIR) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
