/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:21:39 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/23 00:10:21 by mbelouar         ###   ########.fr       */
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

void	ft_red_in(t_data *data, t_tokenizer *head)
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
		err_msg(data, "minishell: ", 1);
		ft_putstr_fd(curr->content, 2);
		err_msg(data, ": No such file or directory\n", 1);
	}
}

void	ft_heredoc(t_data *data, char *delimiter)
{
	int		fd[2];
	int		quotes;
	char	*line;
	char	*expanded;

	pipe(fd);
	signal(SIGINT, signal_heredoc);
	quotes = has_quotes(delimiter);
	if (quotes == 1)
		delimiter = ft_remove_quotes(delimiter);
	while (1)
	{
		line = readline("heredoc> ");
		if (!ft_strcmp(line, delimiter))
			break ;
		expanded = get_expand(data, line, data->env);
		check_heredoc(expanded, line, fd, quotes);
		free(line);
	}
	if (line)
		free(line);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
}

void	setup_redirections(t_data *data, t_tokenizer *head)
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
			ft_red_in(data, curr);
		else if (curr->type == HEREDOC)
			ft_heredoc(data, curr->content);
		curr = curr->next;
	}
}
