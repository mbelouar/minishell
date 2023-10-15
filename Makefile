# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 18:42:22 by mbelouar          #+#    #+#              #
#    Updated: 2023/10/15 20:43:13 by mbelouar         ###   ########.fr        #
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
		srcs/execution/exec.c \
		srcs/execution/redir.c \
		srcs/execution/utils_exec.c \
		srcs/execution/utils2_exec.c \
		srcs/execution/simple_cmd.c \
		srcs/execution/compound_cmd.c \
		srcs/execution/ft_errors.c \
		srcs/execution/signals.c \
		srcs/analylizer/analylizer.c \


RLFLGS        = -L/goinfre/mbelouar/homebrew/opt/readline/lib -lreadline
RLOFLGS        = -I/goinfre/mbelouar/homebrew/opt/readline/include

LIBFT	= libft/libft.a
NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
RM = rm -f
OBJS := $(SRC:.c=.o)
INCLUDE	= -L libft -lft -L/goinfre/mbelouar/homebrew/opt/readline/lib -lreadline #-I ../minishell.h

all: $(NAME) clean

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(FLAGS) -o $(NAME)  $(OBJS) $(INCLUDE) $(RLFLGS)

%.o: %.c
	@$(CC)  -I/goinfre/mbelouar/homebrew/opt/readline/include -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@ make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
