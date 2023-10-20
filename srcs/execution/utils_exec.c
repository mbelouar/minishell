/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrital- <mrital-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:47:48 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/20 15:52:57 by mrital-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_cmds(t_tokenizer *lst)
{
	t_tokenizer	*curr;
	int			i;

	curr = lst;
	i = 0;
	while (curr)
	{
		if (curr->type == CMD || curr->type == BUILTIN)
			i++;
		curr = curr->next;
	}
	return (i);
}

int	check_pipe(t_tokenizer *lst)
{
	t_tokenizer	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->content[0] == '|')
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	exec_cmd(t_data *data, char **cmd, char *cmd_name)
{
	t_tokenizer	*curr;
	curr = data->tokenizer;
	// if(!curr)
	// 	return;
	while (curr)
	{
		if (curr->type == CMD)
		{
			cmd = ft_split(curr->content, ' ');
			cmd_name = get_absolute_path(cmd[0], data);
		}
		curr = curr->next;
	}
	if (cmd_name)
	{
		if (execve(cmd_name, cmd, data->env) == -1)
			perror_exec();
	}
	else if (builtin_check(cmd[0]) == 0 || cmd_name == NULL)
	{
		error_sentence("minishell: command not found\n");
		exit(127);
	}
}

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
