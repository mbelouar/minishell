/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 03:22:02 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/23 05:39:44 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to create a new node
t_tokenizer *new_node(char *content, t_type type)
{
	t_tokenizer *newNode = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	if (newNode == NULL)
		exit(EXIT_FAILURE);

	newNode->content = ft_strdup(content);
	newNode->type = type;
	newNode->next = NULL;

	return (newNode);
}

// Function to add a node to the back of the linked list
void ft_create_node(t_tokenizer **head, char *content, t_type type)
{
	t_tokenizer *newNode = new_node(content, type);

	if (*head == NULL)
		*head = newNode;
	else
	{
		// Traverse the list to find the last node
		t_tokenizer *current = *head;
		while (current->next != NULL)
			current = current->next;
		// Add the new node to the back
		current->next = newNode;
	}
}

void	ft_redirection(t_data *data, char **arr, int *i)
{
	if (arr[*i][0] == '>' && arr[*i][1] == '\0')
		ft_create_node(&data->tokenizer, arr[++(*i)], RED_OUT_TRUNC);
	else if (arr[*i][0] == '>' && arr[*i][1] == '>' && arr[*i][2] == '\0')
		ft_create_node(&data->tokenizer, arr[++(*i)], RED_OUT_APPEND);
	else if (arr[*i][0] == '<' && arr[*i][1] == '\0')
		ft_create_node(&data->tokenizer, arr[++(*i)], RED_IN);
	else
		ft_create_node(&data->tokenizer, arr[++(*i)], HEREDOC);
}

void	tokenizer(t_data *data, char **arr)
{
	int		i;
	char	*cmd;

	i = 0;
	while (arr[i])
	{
		if (arr[i][0] == '>' || arr[i][0] == '<')
			ft_redirection(data, arr, &i);
		else if (arr[i][0] == '|')
		{
			i++;
			ft_create_node(&data->tokenizer, NULL, PIPE);
		}
		else
		{
			while (arr[i] && arr[i][0] != '<' && arr[i][0] != '|'
					&& arr[i][0] != '>')
			{
				cmd = ft_strdup("");
				cmd = ft_strjoin(cmd, arr[i]);
				printf("command is : %s \n", cmd);
				i++;
			}
			ft_create_node(&data->tokenizer, cmd, CMD);
		}
		i++;
	}
}
