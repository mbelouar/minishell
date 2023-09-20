/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:21:12 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/19 20:21:12 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_env_pwd(t_data *data)
{
	char *pwd;

	data->pwd = getcwd(NULL, 0);
	if (var_index("PWD", data) >= 0)
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		replace_var(pwd, data, var_index(pwd, data));
		free(pwd);
	}
	else
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		data->env = export_env(data->env, pwd);
		free(pwd);
	}
}

void	change_env_oldpwd(t_data *data)
{
	char *pwd;
	char *oldpwd;

	if (var_index("OLDPWD", data) >= 0)
	{
		pwd = ft_strjoin("PWD=", data->pwd);
		oldpwd = ft_strjoin("OLD", pwd);
		replace_var(oldpwd, data, var_index("OLDPWD=", data));
		free(oldpwd);
		free(pwd);
	}
	else
		data->env = export_env(data->env, "OLDPWD");
	free(data->pwd);
}

int		change_pwd(t_data *data, char *input)
{
	char	*prev_wd;
	char	*curr_wd;

	curr_wd = getcwd(NULL, 0);
	if (!curr_wd && input && ft_strcmp(".", input) == 0)
	{
		ft_putstr_fd("Error retrieving current directory\n", 2);
		prev_wd = data->prev_wd;
		data->prev_wd = ft_strjoin(prev_wd, "/.");
		free(prev_wd);
	}
	if (curr_wd)
	{
		change_env_oldpwd(data);
		change_env_pwd(data);
	}
	free(curr_wd);
	return (1);
}
