/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:02:30 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/19 23:35:25 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	end_of_file(t_data *data)
// {
// 	free_env(data->env);
// 	free(user_input);
// 	free(data->pwd);
// 	ft_putstr_fd("exit\n", 2);
// 	exit(EXIT_SUCCESS);
// }

// void	data_init(t_data *data, char **env)
// {
// 	data->env = dup_env(env);
// 	data->pwd = getcwd(NULL, 0);
// 	data->fd_in = 0;
// 	data->fd_out = 1;
// 	data->redir = 1;
// }

int		main(int ac, char **av, char **env)
{
	t_data	data;
	char*		line;

	ac = 0;
	av = NULL;
	// data_init(&data, env);
	// if (!data.env)
		// exit(EXIT_FAILURE);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (1);
		char	**tmp = ft_split(line, ' ');
		if (!tmp)
			continue ;
		for (int i = 0; tmp[i]; i++)
			printf("%s\n", tmp[i]);
		// if (!line)
		// 	end_of_file(&data);
		// else
		// 	parser_start(&data);
	}
	return (0);
}
