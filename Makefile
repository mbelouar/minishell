# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 18:42:22 by mbelouar          #+#    #+#              #
#    Updated: 2023/09/24 04:04:15 by mbelouar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 # Colors
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m
YELLOW = \033[0;33m

SRC =	main.c \
	 	srcs/builtins/ft_cd.c \
		srcs/builtins/ft_echo.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_exit.c \
		srcs/builtins/ft_export.c \
		srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_unset.c \
		srcs/builtins/cd_utils.c \
		srcs/builtins/export_utils.c \
		srcs/parser/tokenizer.c \
		srcs/parser/tokenizer_utils.c \

LIBFT	= libft/libft.a
NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -f
OBJS := $(SRC:.c=.o)
INCLUDE	= -L libft -lft #-I ../minishell.h

all: $(NAME) clean

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(FLAGS) -o $(NAME)  $(OBJS) $(INCLUDE) -lreadline

%.o: %.c
	@$(CC) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@ make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
