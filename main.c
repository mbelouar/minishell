/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:02:30 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/29 23:15:00 by mbelouar         ###   ########.fr       */
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
	data->pwd = getcwd(NULL, 0);
	data->exit_status = 0;
}

void	create_lst(t_data *data, char **arr)
{
	int	i;

	i = 0;
	t_list	*new_node;
	while (arr[i])
	{
		new_node = ft_lstnew(arr[i]);
		ft_lstadd_back(&data->lst, ft_lstnew(arr[i]));
		i++;
	}
}

void print_lst(t_list *head) {
    t_list *current = head;
    while (current != NULL) {
        printf("==> %s\n", current->content);
        current = current->next;
    }
}

int	ft_token_size(t_tokenizer *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

int		main(int ac, char **av, char **env)
{
	t_data	data;
	char	*line;
	char	**tmp;

	(void)ac;
	(void)av;
	tmp = NULL;
	data_init(&data, env);
	if (!data.env)
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline("> ");
		if (!line)
			end_of_file(&data);
		tmp = ft_split(line, ' ');
		if (!tmp)
			return (1);
		create_lst(&data, tmp);
		tokenizer(&data);
		// printList(data.tokenizer);
		print_lst(data.lst);
		// execute(&data);
		// free_double_pointer(tmp);
		free_token_list(&data.tokenizer);
		ft_lstclear(&data.lst);
		// system("leaks -q minishell");
	}
	return (0);
}
