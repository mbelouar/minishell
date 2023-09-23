/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 04:31:55 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/23 05:43:25 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to print the name of an enum value
void printEnumName(enum e_type value)
{
	// An array of strings to map enum values to their names
	const char *e_type_names[] = {
		"CMD",
		"BUILTIN",
		"PIPE",
		"RED_OUT_TRUNC",
		"RED_OUT_APPEND",
		"RED_IN",
		"HEREDOC"
	};

	if (value == CMD)
		printf("Type: %s\n", e_type_names[0]);
	if (value == BUILTIN)
		printf("Type: %s\n", e_type_names[1]);
	if (value == PIPE)
		printf("Type: %s\n", e_type_names[2]);
	if (value == RED_OUT_TRUNC)
		printf("Type: %s\n", e_type_names[3]);
	if (value == RED_OUT_APPEND)
		printf("Type: %s\n", e_type_names[4]);
	if (value == RED_IN)
		printf("Type: %s\n", e_type_names[5]);
	if (value == HEREDOC)
		printf("Type: %s\n", e_type_names[6]);
}


void free_token_list(t_tokenizer *head)
{
	t_tokenizer *current = head;
	t_tokenizer *next;

	while (current != NULL)
	{
		next = current->next; // Save the reference to the next node
		free(current->content); // Free the content (assuming it was dynamically allocated)
		free(current); // Free the current node
		current = next; // Move to the next node
	}
}

void printList(t_tokenizer *head)
{
	t_tokenizer *current = head;
	while (current != NULL)
	{
		printf("Content: %s\t", current->content);
		printEnumName(current->type);
		current = current->next;
	}
}
