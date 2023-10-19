# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 18:42:22 by mbelouar          #+#    #+#              #
#    Updated: 2023/10/19 22:07:30 by mbelouar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
		srcs/expand/expand.c \
		srcs/expand/expand_utils.c \
		srcs/expand/expand_utils2.c \


RLFLGS        = -L/goinfre/mbelouar/homebrew/opt/readline/lib -lreadline
RLOFLGS        = -I/goinfre/mbelouar/homebrew/opt/readline/include

LIBFT	= libft/libft.a
NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
RM = rm -f
OBJS := $(SRC:.c=.o)
INCLUDE	= -L libft -lft -L/goinfre/mbelouar/homebrew/opt/readline/lib -lreadline #-I ../minishell.h

%.o: %.c
	@$(CC)  -I/goinfre/mbelouar/homebrew/opt/readline/include -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(FLAGS) -o $(NAME)  $(OBJS) $(INCLUDE) $(RLFLGS)


clean:
	@$(RM) $(OBJS)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@ make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
