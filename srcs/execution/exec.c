/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:42:40 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/22 19:45:26 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_path_environment(t_data *data)
{
	int		i;
	char	*path_env;

	i = 0;
	path_env = NULL;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH", 4) == 0)
		{
			path_env = data->env[i];
			break ;
		}
		i++;
	}
	return (path_env);
}

char	*search_in_path(char *cmd_name, char *path_copy)
{
	char	*path;
	char	*token;
	char	abs_path[MAX_PATH_LENGTH];
	char	*result;

	result = NULL;
	path = path_copy;
	while (1)
	{
		token = ft_strsep(&path, ":");
		if (token == NULL)
			break ;
		snprintf(abs_path, sizeof(abs_path), "%s/%s", token, cmd_name);
		if (access(abs_path, X_OK) == 0)
		{
			result = ft_strdup(abs_path);
			break ;
		}
	}
	return (result);
}

void	check_dir(char *command_name, t_data *data)
{
	DIR	*dir;

	dir = opendir(command_name);
	if (dir != NULL)
	{
		err_msg(data, "minishell: ", 126);
		ft_putstr_fd(command_name, 2);
		err_msg(data, ": is a directory\n", 126);
		closedir(dir);
		exit(126);
	}
}

char	*get_absolute_path(char *command_name, t_data *data)
{
	int		i;
	char	*path_env;
	char	absolute_path[MAX_PATH_LENGTH];
	char	*path_copy;
	char	*result;

	i = 0;
	result = NULL;
	check_dir(command_name, data);
	if (access(command_name, F_OK | X_OK) == 0)
		return (command_name);
	path_env = get_path_environment(data);
	if (path_env == NULL)
	{
		err_msg(data, "PATH environment variable is not set\n", 127);
		return (NULL);
	}
	path_copy = ft_strdup(path_env);
	if (path_copy == NULL)
		return (NULL);
	result = search_in_path(command_name, path_copy);
	free(path_copy);
	return (result);
}

void	execute(t_data *data)
{
	if (!data->tokenizer)
		return ;
	if (check_pipe(data->tokenizer) == 0)
		execute_simple_cmd(data);
	else
		execute_compound_command(data);
}
