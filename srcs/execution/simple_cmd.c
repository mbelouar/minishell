/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:51:59 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/29 22:19:53 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_simple_cmd(t_data *data)
{
	t_tokenizer	*curr;
	t_tokenizer	*tmp;
	pid_t		pid;
	char		**cmd;
	char		*cmd_name;

	curr = data->tokenizer;
	cmd_name = NULL;
	tmp = data->tokenizer;
	while (tmp)
	{
		if (tmp->type == BUILTIN)
		{
			cmd = ft_split(tmp->content, ' ');
			exec_builtin(cmd, data);
			free_double_pointer(cmd);
			return ;
		}
		tmp = tmp->next;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("error in fork:");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		setup_redirections(data->tokenizer);
		while (curr)
		{
			if (curr->type == CMD)
			{
				cmd = ft_split(curr->content, ' ');
				cmd_name = get_absolute_path(cmd[0]);
			}
			curr = curr->next;
		}
		if (cmd_name)
		{
			if (execve(cmd_name, cmd, data->env) == -1)
			{
				perror("error in execve:");
				exit(EXIT_FAILURE);
			}
		}
		else if (builtin_check(cmd[0]) == 0 || cmd_name == NULL)
		{
			dprintf(2, "minishell: command not found: %s\n", cmd[0]);
			exit(127); // to be changed
		}
	}
}

