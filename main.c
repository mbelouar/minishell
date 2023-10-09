/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:02:30 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/09 18:13:59 by mbelouar         ###   ########.fr       */
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
}

void	create_lst(t_data *data, char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_lstadd_back(&data->lst, ft_lstnew(arr[i]));
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
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
	t_list	*lst;
	int err;

	tmp = NULL;
	data_init(&data, env);
	if (!data.env)
		exit(EXIT_FAILURE);
	if (ac && av[0])
	{
		while (1)
		{
			line = readline("> ");
			if (!line)
				end_of_file(&data);
			else
				add_history(line);
				tmp = ft_split(line, ' ');
				create_lst(&data, tmp);
				err = check_quotes(line);
				if (err == 0)
				{
					printf("syntax error \n");
					free_token_list(&data.tokenizer);
					ft_lstclear(&data.lst);
					free(line);
					continue ;
				}
				lst = ft_split_lst(line,'\0');
				err = analylizer(lst);
				if (err == 1)
				{
					printf("minishell: syntax error near unexpected token\n");
					free_token_list(&data.tokenizer);
					ft_lstclear(&data.lst);
					ft_lstclear(&lst);
					free(line);
					continue ;
				}
				ft_lstclear(&lst);
				tokenizer(&data);
				execute(&data);
				free(line);
				free_token_list(&data.tokenizer);
				ft_lstclear(&data.lst);
				system("leaks -q minishell");
		}
	}
	return (0);
}
