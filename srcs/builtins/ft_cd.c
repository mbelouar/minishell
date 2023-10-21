/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:26 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/21 19:54:49 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getenv(char **env, char *to_get)
{
	int		i;
	char	*value;
	char	*name;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], to_get, 4) == 0)
		{
			name = ft_strtok(env[i], "=");
			value = ft_strtok(NULL, "=");
			if (name != NULL && value != NULL && ft_strcmp(name, to_get) == 0)
				return (value);
		}
		i++;
	}
	return (NULL);
}

int	cd_minus(t_data *data)
{
	char	*oldpwd_env;

	oldpwd_env = getenv("OLDPWD");
	if (oldpwd_env == NULL || chdir(oldpwd_env) == -1)
		return (0);
	change_pwd(data, NULL);
	return (1);
}

int	cd_alone(t_data *data)
{
	char	*home_env;

	home_env = ft_getenv(data->env, "HOME");
	if (home_env == NULL || chdir(home_env) == -1)
		return (0);
	change_pwd(data, NULL);
	return (1);
}

int	cd_path(char **args, t_data *data)
{
	if (chdir(args[1]) == -1)
		return (0);
	change_pwd(data, args[1]);
	return (1);
}

void	ft_cd(char **args, t_data *data)
{
	if (!args[1])
	{
		if (!cd_alone(data))
			return (error_sentence(data, "cd: HOME: is undefined\n", 1));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (!cd_minus(data))
			return (error_sentence(data, "cd: OLDPWD is undefined\n", 1));
	}
	else
	{
		if (!cd_path(args, data))
			return (error_sentence(data, "cd: no such file or directory\n", 1));
	}
}
