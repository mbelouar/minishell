/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:02:30 by mrital-           #+#    #+#             */
/*   Updated: 2023/10/23 01:37:37 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_file(t_data *data)
{
	free_env(data->env);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	g_status = 0;
	exit(EXIT_SUCCESS);
}

void	data_init(t_data *data, char **env)
{
	data->exit_status = 0;
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

static void	ft_hacker(char *line, t_data *data, t_list *lst, char **tmp)
{
	while (1)
	{
		line = ft_readline(data);
		if (!line)
			continue ;
		tmp = ft_split(line, ' ');
		create_lst(data, tmp);
		if (check_quotes(line) == 1)
		{
			ft_quotes_err(data, line);
			continue ;
		}
		lst = ft_split_lst(line, '\0');
		if (analylizer(lst) == 1)
		{
			ft_syntax_err(data, line, lst);
			continue ;
		}
		tokenizer(data);
		execute(data);
		ft_lstclear(&lst);
		free(line);
		free_token_list(&data->tokenizer);
		ft_lstclear(&data->lst);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_list	*lst;
	char	*line;
	int		err;

	data_init(&data, env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (ac && av[0])
		ft_hacker(line, &data, lst, NULL);
	return (0);
}
