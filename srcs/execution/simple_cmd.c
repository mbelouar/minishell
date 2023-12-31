/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:51:59 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/23 16:35:32 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_builtin_cmd(t_data *data, int save_fd[2])
{
	t_tokenizer	*tmp;
	char		**cmd;

	tmp = data->tokenizer;
	while (tmp)
	{
		if (tmp->type == BUILTIN)
		{
			cmd = ft_split(tmp->content, ' ');
			save_fd[0] = dup(0);
			save_fd[1] = dup(1);
			setup_redirections(data, tmp);
			exec_builtin(cmd, data);
			dup2(save_fd[0], 0);
			dup2(save_fd[1], 1);
			close(save_fd[0]);
			close(save_fd[1]);
			free_double_pointer(cmd);
			return ;
		}
		tmp = tmp->next;
	}
}

void	execute_external_cmd(t_data *data, int __unused save_fd[2])
{
	t_tokenizer	*tmp;
	pid_t		pid;
	char		**cmd;
	char		*cmd_name;
	int			status;

	cmd = NULL;
	tmp = data->tokenizer;
	cmd_name = NULL;
	pid = fork();
	if (pid < 0)
		perror_fork();
	else if (pid == 0)
	{
		setup_redirections(data, data->tokenizer);
		exec_cmd(data, cmd, cmd_name);
	}
	else
	{
		waitpid(pid, &status, 0);
		data->exit_status = WEXITSTATUS(status);
	}
}

void	execute_simple_cmd(t_data *data)
{
	int	save_fd[2];

	if (builtin_check(data->lst->content))
		execute_builtin_cmd(data, save_fd);
	else
		execute_external_cmd(data, save_fd);
}
