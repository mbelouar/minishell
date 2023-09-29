/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:53:28 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/29 21:10:29 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_builtin(char **cmd, t_data *data)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd, data);
	if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(cmd, data);
	if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(data->env);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd(data);
	if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
	if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd, data);
}
