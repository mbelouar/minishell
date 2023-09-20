/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:02:30 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/20 23:06:17 by mbelouar         ###   ########.fr       */
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

void print_arr(char **arr)
{
	for(int i = 0; arr[i]; i++)
		printf("arr[%d]: %s\n", i, arr[i]);
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
