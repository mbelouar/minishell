/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:28:00 by mrital-           #+#    #+#             */
/*   Updated: 2023/10/23 17:00:40 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tokenizer	*new_node(char *content, t_type type)
{
	t_tokenizer	*n_node;

	n_node = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	if (n_node == NULL)
		exit(EXIT_FAILURE);
	n_node->content = ft_strdup(content);
	n_node->type = type;
	n_node->next = NULL;
	return (n_node);
}

void	ft_create_node(t_tokenizer **head, char *content, t_type type)
{
	t_tokenizer	*n_node;
	t_tokenizer	*current;

	n_node = new_node(content, type);
	if (*head == NULL)
		*head = n_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = n_node;
	}
}

void	ft_redirection(t_list *curr_node, t_data *data)
{
	static t_type	type;
	char			*content;

	content = NULL;
	if (curr_node->content[0] == '>' && curr_node->content[1] == '>')
	{
		type = RED_OUT_APPEND;
		content = curr_node->next->content;
	}
	else if (curr_node->content[0] == '>')
	{
		type = RED_OUT_TRUNC;
		content = curr_node->next->content;
	}
	else if (curr_node->content[0] == '<' && curr_node->content[1] == '<')
	{
		type = HEREDOC;
		content = curr_node->next->content;
	}
	else if (curr_node->content[0] == '<')
	{
		type = RED_IN;
		content = curr_node->next->content;
	}
	ft_create_node(&data->tokenizer, content, type);
}

int	builtin_check(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	return (0);
}
