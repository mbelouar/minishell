/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:02:30 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/22 22:46:47 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_file(t_data *data)
{
	free_env(data->env);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}

void	data_init(t_data *data, char **env)
{
	data->env = dup_env(env);
	data->pwd = getcwd(NULL, 0); //
	data->exit_status = 0;
}

void print_arr(char **arr)
{
	for(int i = 0; arr[i]; i++)
		printf("arr[%d]: %s\n", i, arr[i]);
}

// Function to print the name of an enum value
void printEnumName(enum e_type value)
{
	// An array of strings to map enum values to their names
	const char *e_type_names[] = {
		"CMD",
		"BUILTIN",
		"PIPE",
		"RED"
	};

	if (value == CMD)
		printf("Type: %s\n", e_type_names[0]);
	if (value == BUILTIN)
		printf("Type: %s\n", e_type_names[1]);
	if (value == PIPE)
		printf("Type: %s\n", e_type_names[2]);
	if (value == RED)
		printf("Type: %s\n", e_type_names[3]);
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

// Function to create a new node
t_tokenizer *createNode()
{
	t_tokenizer *newNode = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	if (newNode == NULL)
		exit(EXIT_FAILURE);

	newNode->content = NULL;
	newNode->type = -1;
	newNode->next = NULL;

	return (newNode);
}

// Function to add a node to the back of the linked list
void ft_create_node(t_tokenizer **head, t_tokenizer *new_node)
{
	// t_tokenizer *newNode = createNode(content, type);

	if (*head == NULL)
	{
		// If the list is empty, make the new node the head
		*head = newNode;
	}
	else
	{
		// Traverse the list to find the last node
		t_tokenizer *current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		// Add the new node to the back
		current->next = newNode;
	}
}

void	ft_redirection(t_tokenizer *new_node, char **arr, int *i)
{
	*(i)++;
}

void	tokenizer(t_data *data, char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		t_tokenizer *new_node = createNode();
		if (arr[i][0] == '>')
		{
			ft_redirection(new_node, arr, &i);
			// ft_create_node(&(data->tokenizer), arr[i], RED);
		}
		else if (arr[i][0] == '<')
		{
			ft_redirection(new_node, arr, &i);
		}
		else if (arr[i][0] == '|')
		{
			ft_tokenize_pipe(new_node, arr, &i);
		}
		else
		{
			ft_cmd(new_node, arr, &i); // < << > >> |
		}
		i++;
	}
}

int		main(int ac, char **av, char **env)
{
	t_data	data;
	char*		line;

	(void)ac;
	(void)av;
	data_init(&data, env);
	if (!data.env)
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline("> ");
		if (!line)
			end_of_file(&data);
		char	**tmp = ft_split(line, ' ');
		if (!tmp)
			continue;
		if (ft_strcmp(tmp[0], "echo") == 0)
			ft_echo(tmp);
		if (ft_strcmp(tmp[0], "export") == 0)
			ft_export(tmp, &data);
		if (ft_strcmp(tmp[0], "unset") == 0)
			ft_unset(tmp, &data);
		if (ft_strcmp(tmp[0], "env") == 0)
			ft_env(data.env);
		if (ft_strcmp(tmp[0], "pwd") == 0)
			ft_pwd(&data);
		if (ft_strcmp(tmp[0], "exit") == 0)
			ft_exit(tmp);
		if (ft_strcmp(tmp[0], "cd") == 0)
			ft_cd(tmp, &data);
		tokenizer(&data, tmp);
		printList(data.tokenizer);
		// is_builtin();
			// builtin();
		// for (int i = 0; tmp[i]; i++)
		// 	printf("%s\n", tmp[i]);
		// else
		// 	struct = parser_start(&data);
		// 	execute(struct);
	}
	return (0);
}
