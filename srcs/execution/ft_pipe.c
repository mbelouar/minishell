/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:33:23 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/22 21:56:52 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
content  = CMD
check the content is single or compound command
if (single command)
{
	fork;
	execve;
}
else // compound command
{
	pip;
	fork;
	execve;
}
*/

int	ft_pipe(t_data *data, char **env)
{
	int		fd[2]; // fd[1] right end ; fd[0] read end
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		// ft_putstr_fd("An error ocurred with opening the pipeline", 2);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 2; i++)
	{
		char cmd1[] = "/bin/ls";
		char cmd2[] = "/bin/cat";
		char *s1[] = {"/bin/ls", "-la", NULL};
		char *s2[] = {"/bin/cat", "-e", NULL};
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				dup2(fd[1], 1);
				execve(cmd1, s1, env);
			}
			else
			{
				dup2(fd[0], 0);
				execve(cmd2, s2, env);
			}
			// child process
		}
		else
		{
			// if (i == 1)
				// waitpid(pid, 0, 0);
			// parent process
		}
	}
	return (1);
}

int main(int ac, char **av, char **env)
{
	ft_pipe(NULL, env);
	return (0);
}
