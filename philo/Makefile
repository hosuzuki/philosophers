# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/30 14:42:39 by hos               #+#    #+#              #
#    Updated: 2022/09/11 12:09:09 by hos              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
CC		:= gcc -pthread 
CFLAGS	:= -Wall -Wextra -Werror
RM		:= rm -f
HEADERDIR	:=	.

ifeq ($(DEBUG), 1)
CFLAGS	+= -g
endif

ifeq ($(DEBUG), 2)
CFLAGS	+= -fsanitize=thread 
endif

# **************************************************************************** #

SRCS	:= \
	main.c \
	save_argv.c \
	utils.c \
	init_lst.c \
	free_all.c \
	start_simulation.c \
	put_status.c \
	put_status2.c \
	ft_utils.c \
	ft_utils2.c \
	eat_task.c \
	is_end.c \
	sleep_task.c \

# **************************************************************************** #

OBJS	:= $(SRCS:%.c=%.o)
#HEADERS	:= \
	philo.h \
	philo_utils.h \

OBJDIR	= objs/
OBJS	= $(patsubst %.c,$(OBJDIR)%.o, $(notdir $(SRCS)))
DEPS	= $(OBJS:.o=.d)
vpath %.c $(sort $(dir $(SRCS)))

GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ==="
	@printf "\n--- $(notdir $(SRCS))$(RC)\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@printf "$(YE)&&& Linked [$(CC) $(LDFLAGS)] &&&\n--- $(NAME)$(RC)\n"

#$(CC) $(OBJS) $(addprefix -I,$(HEADERDIR)) -o $(NAME)
#.c.o:
#	$(CC) $(CFLAGS) -c $< -o $@

#.SUFFIXES: .o .c

-include $(DEPS)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "$(GR)+$(RC)"

clean:
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@$(RM) -r $(OBJDIR)

fclean: clean
	@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re

# **************************************************************************** #




