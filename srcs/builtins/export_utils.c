/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:23:08 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/19 20:23:08 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_export(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || str[i] == '=')
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i == 0)
				return (0);
			i++;
			break ;
		}
		i++;
	}
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == 39 || str[i] == 34)
			i++;
		else
			return (0);
	}
	return (1);
}

void	replace_var(char *new_var, t_data *data, int index)
{
	if (ft_strchr(new_var, '='))
	{
		free(data->env[index]);
		data->env[index] = ft_strdup(new_var);
	}
}

int	print_export(char **env)
{
	int	i;
	int	j;
	int	equal;

	i = -1;
	while (env[++i])
	{
		equal = 1;
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][j])
		{
			if (env[i][j] == '\\' || env[i][j] == '$' || env[i][j] == '\"')
				write(1, "\\", 1);
			write(1, &env[i][j], 1);
			if (env[i][j] == '=' && equal-- == 1)
				write(1, "\"", 1);
			j++;
		}
		if (equal != 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
	return (1);
}

char	**dup_env(char **env)
{
	char	**data_env;
	int		i;

	i = 0;
	data_env = ft_calloc((envlen(env) + 1), sizeof(char *));
	if (!data_env)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		data_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (data_env);
}
