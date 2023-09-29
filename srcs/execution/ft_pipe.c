/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:33:23 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/27 17:05:32 by mbelouar         ###   ########.fr       */
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
		ft_putstr_fd("An error ocurred with opening the pipeline", 2);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		// child process
	}
	else
	{
		// parent process
		// waitpid(pid, 0, 0);
	}
	return (1);
}
