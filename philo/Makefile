# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hos <hosuzuki@student.42tokyo.jp>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/30 14:42:39 by hos               #+#    #+#              #
#    Updated: 2022/09/16 20:48:17 by hos              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
CC		:= gcc -pthread 
CFLAGS	:= -Wall -Wextra -Werror
RM		:= rm -f

ifeq ($(DEBUG), 1)
CFLAGS	+= -g3
endif

ifeq ($(DEBUG), 2)
CFLAGS	+= -fsanitize=thread 
endif

# **************************************************************************** #

SRCS	:= \
	main.c \
	save_argv.c \
	init_lst.c \
	start_simulation.c \
	eat_task.c \
	sleep_task.c \
	put_status.c \
	is_end.c \
	free_all.c \
	utils.c \
	ft_utils.c \
	ft_utils2.c \

# **************************************************************************** #

OBJS	:= $(SRCS:%.c=%.o)

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
	@printf "$(YE)--- $(NAME)$(RC)\n"

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
