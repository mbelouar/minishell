# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 18:42:22 by mbelouar          #+#    #+#              #
#    Updated: 2023/09/15 18:46:51 by mbelouar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 # Colors
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m
YELLOW = \033[0;33m

SRC = 	srcs/builtins/ft_cd.c \
		srcs/builtins/ft_echo.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_exit.c \
		srcs/builtins/ft_export.c \
		srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_unset.c \

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g
RM = rm -f
OBJS := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)
	@echo "$(GREEN)Compilation complete$(RESET)"

$(OBJS): %.o: %.c
	@echo "$(YELLOW)Compiling $< $(RESET)"
	@$(CC) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
