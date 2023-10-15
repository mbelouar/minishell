/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:21:39 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/15 20:41:17 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_red_out_trunc(t_tokenizer *head)
{
	t_tokenizer	*curr;
	int			fd;

	curr = head;
	fd = open(curr->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
}

void	ft_red_out_append(t_tokenizer *head)
{
	t_tokenizer	*curr;
	int			fd;

	curr = head;
	fd = open(curr->content, O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
}

void	ft_red_in(t_tokenizer *head)
{
	t_tokenizer	*curr;
	int			fd;

	curr = head;
	if (access(curr->content, F_OK) == 0)
	{
		fd = open(curr->content, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		error_sentence("minishell: ");
		ft_putstr_fd(curr->content, 2);
		error_sentence(": No such file or directory\n");
		exit(EXIT_FAILURE);
	}
}

void	ft_heredoc(char		*delimiter)
{
	// check if delimiter has quotes -> true dont expand else expand
	int			fd[2];
	char		*line;
	// char		*expanded;
	int			has_quotes;

	pipe(fd);
	signal(SIGINT, signal_heredoc);
	while (1)
	{
		line = readline("heredoc> ");
		if (!ft_strcmp(line, delimiter))
			break ;
		// expanded = ft_expander(line);
		// if (expanded && !has_quotes)
		// 	write(pipe_fd[1], expanded, ft_strlen(expanded));
		// else
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
}

void	setup_redirections(t_tokenizer *head)
{
	t_tokenizer	*curr;

	curr = head;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == RED_OUT_TRUNC)
			ft_red_out_trunc(curr);
		else if (curr->type == RED_OUT_APPEND)
			ft_red_out_append(curr);
		else if (curr->type == RED_IN)
			ft_red_in(curr);
		else if (curr->type == HEREDOC)
			ft_heredoc(curr->content);
		curr = curr->next;
	}
}

