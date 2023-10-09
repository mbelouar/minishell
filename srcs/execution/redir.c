/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:21:39 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/09 21:55:22 by mbelouar         ###   ########.fr       */
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
		dprintf(2, "minishell: %s: No such file or directory\n", curr->content);
		exit(EXIT_FAILURE);
	}
}
