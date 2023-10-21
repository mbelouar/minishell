/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:42:40 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/21 19:58:24 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_absolute_path(char *command_name, t_data *data)
{
	DIR		*dir;
	int		i;
	char	*path_env;

	i = 0;
	dir = opendir(command_name);
	if (dir != NULL)
	{
		error_sentence(data, "minishell: ", 126);
		ft_putstr_fd(command_name, 2);
		error_sentence(data, ": is a directory\n", 126);
		closedir(dir);
		exit(126);
	}
	if (access(command_name, F_OK | X_OK) == 0)
		return (command_name);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH", 4) == 0)
		{
			path_env = data->env[i];
			break ;
		}
		i++;
	}
	if (path_env == NULL) {
		error_sentence(data, "PATH environment variable is not set\n", 127);
		return (NULL);
	}
	char *path_copy = ft_strdup(path_env);
	if (path_copy == NULL) {
		perror("Memory allocation failed");
		return NULL;
	}

	char *path = path_copy;
	char *token;
	char *result = NULL;

	while ((token = ft_strsep(&path, ":")) != NULL) {
		char absolute_path[MAX_PATH_LENGTH];
		snprintf(absolute_path, sizeof(absolute_path), "%s/%s", token, command_name);

		if (access(absolute_path, X_OK) == 0) {
			result = ft_strdup(absolute_path);
			break ;
		}
	}
	free(path_copy);
	return (result);
}

void	execute(t_data *data)
{
	if (check_pipe(data->tokenizer) == 0)
		execute_simple_cmd(data);
	else
		execute_compound_command(data);
}
