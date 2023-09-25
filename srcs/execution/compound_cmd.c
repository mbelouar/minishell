/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:53:00 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/24 18:53:28 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_compound_command(t_data *data)
{
	int	i;
	int	nb;
	int	pipe_fd[2];
	int	prev_in;
	pid_t	pid;
	char	**cmd;
	char 	*cmd_name = NULL;

	i = 0;
	prev_in = 0;
	nb = count_cmds(data->tokenizer);
	t_tokenizer	*curr;
	curr = data->tokenizer;
	while (i < nb)
	{
		while (curr && curr->type != PIPE)
		{
			if (curr->type == CMD)
			{
				cmd = ft_split(curr->content, ' ');
				cmd_name = get_absolute_path(cmd[0]);
				break ;
			}
			curr = curr->next;
		}
		if (i != (nb - 1))
		{
			curr = curr->next->next;
			pipe(pipe_fd);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("error:");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			dup2(prev_in, STDIN_FILENO);
			close(pipe_fd[0]);
			if (i != (nb - 1))
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			if (i == 0)
				setup_redirections(data->tokenizer);
			else
				setup_redirections(curr);
			printf("cmd_name: %s\n", cmd_name);
			execve(cmd_name, cmd, data->env);
			perror("error: ");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (i == (nb - 1))
				waitpid(pid, 0, 0);
			if (prev_in)
				close(prev_in);
			prev_in = dup(pipe_fd[0]);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		i++;
	}
}
