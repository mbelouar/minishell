/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:37 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/18 22:04:58 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		var_index(char *name, t_data *data)
{
	int		j;
	int		i;

	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j] && data->env[i][j] == name[j]
		&& name[j] != '\0' && name[j] != '=' &&
		data->env[i][j] != '\0' && data->env[i][j] != '=')
			j++;
		if ((data->env[i][j] == '\0' || data->env[i][j] == '=') &&
		(name[j] == '\0' || name[j] == '='))
			return (i);
		i++;
	}
	return (-1);
}

void	replace_var(char *new_var, t_data *data, int index)
{
	if (ft_strchr(new_var, '='))
	{
		free(data->env[index]);
		data->env[index] = ft_strdup(new_var);
	}
}

char	**export_env(char **old_env, char *export)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (envlen(old_env) + 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	free_env(old_env);
	new_env[i] = ft_strdup(export);
	i++;
	new_env[i] = NULL;
	return (new_env);
}

void	export_alone(t_data *data)
{
	int		i;
	int		j;
	char	**temp_env;
	char	*swap;

	i = 0;
	temp_env = dup_env(data->env);
	while (temp_env[i + 1])
	{
		j = i + 1;
		if (ft_strcmp(temp_env[i], temp_env[j]) > 0)
		{
			swap = temp_env[j];
			temp_env[j] = temp_env[i];
			temp_env[i] = swap;
			i = 0;
		}
		else
			i++;
	}
	print_export(temp_env);
	free_env(temp_env);
}

void ft_export(char **args, t_data *data)
{
    int i;
    int index;

    i = 1;
    if (args[i])
    {
        while (args[i])
        {
            index = var_index(args[i], data);
            if (check_export(args[i]))
            {
                if (index >= 0)
                    replace_var(args[i], data, index);
                else
                {   // The variable doesn't exist, add it to the environment.
                    data->env = export_env(data->env, args[i]);
                    if (!data->env)
                        exit(EXIT_FAILURE);
                }
            }
            else
                return error_sentence("export: bad identifier\n");
            i++;
        }
    }
    else
        export_alone(data);
}