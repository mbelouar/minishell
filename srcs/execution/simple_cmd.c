/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:51:59 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/24 18:52:40 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_simple_cmd(t_data *data)
{
	t_tokenizer	*curr;
	// add function that retreive the asbsolute path of the command
	char	**cmd;
	char 	*cmd_name = NULL;

	curr = data->tokenizer;
	// cmd = ft_split(curr->content, ' ');
	// if (builtin_check(cmd[0]))
		// exec_builtin();
	// else
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("error:");
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
			execve(cmd_name, cmd, data->env);
			perror("");
			exit(EXIT_FAILURE);
		}
		dprintf(2, "minishell: %s: command not found\n", cmd[0]);
		exit(127); // to be changed
	}
	else
	{
		waitpid(pid, 0, 0);
	}
}

