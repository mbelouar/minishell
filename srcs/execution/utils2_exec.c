/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:43:56 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/21 21:34:17 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_in_child(t_pipe p, t_data *data)
{
	if (p.cmd_name)
	{
		execve(p.cmd_name, p.cmd, data->env);
		perror_exec();
	}
	else
	{
		error_sentence(data, "minishell: command not found\n", 127);
		exit(127);
	}
}

void	child_exec(t_data *data, t_pipe p, int i, t_tokenizer *curr)
{
	if (i < (p.cmd_nb - 1))
	{
		dup2(p.pipe_fd[1], STDOUT_FILENO);
		close(p.pipe_fd[1]);
	}
	if (i > 0)
		dup2(p.prev_in, STDIN_FILENO);
	close(p.pipe_fd[0]);
	setup_redirections(data, curr);
	if (builtin_check(p.cmd[0]))
	{
		exec_builtin(p.cmd, data);
		exit(0);
	}
	else
		exec_in_child(p, data);
}
