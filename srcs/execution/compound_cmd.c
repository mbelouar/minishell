/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:53:00 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/01 17:14:40 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_compound_command(t_data *data)
{
	int			i;
	t_pipe		p;
	t_tokenizer	*curr;

	i = 0;
	p.prev_in = 0;
	p.cmd_name = NULL;
	p.cmd_nb = count_cmds(data->tokenizer);
	pid_t child_pids[p.cmd_nb];
	curr = data->tokenizer;
	while (i < p.cmd_nb)
	{
		while (curr && curr->type != PIPE)
		{
			if (curr->type == CMD)
			{
				p.cmd = ft_split(curr->content, ' ');
				p.cmd_name = get_absolute_path(p.cmd[0]);
				break ;
			}
			curr = curr->next->next;
		}
		if (i != (p.cmd_nb - 1))
		{
			curr = curr->next->next;
			pipe(p.pipe_fd);
		}
		p.pid = fork();
		if (p.pid < 0)
		{
			perror("error:");
			exit(EXIT_FAILURE);
		}
		else if (p.pid == 0)
		{
			child_exec(data, p, i);
		}
		else
		{
			if (i < p.cmd_nb - 1)
				close(p.pipe_fd[1]);
			if (i > 0)
				close(p.prev_in);
			p.prev_in = p.pipe_fd[0];
		}
		child_pids[i] = p.pid;
		i++;
	}
	i = -1;
	while (++i < p.cmd_nb)
		waitpid(child_pids[i], NULL, 0);
}

// void execute_compound_command(t_data *data)
// {
//     int i;
//     int nb;
//     int pipe_fd[2];
//     int prev_in;
//     pid_t pid;
//     char **cmd;
//     char *cmd_name = NULL;

//     i = 0;
//     prev_in = 0;
//     nb = count_cmds(data->tokenizer);
//     t_tokenizer *curr;
//     curr = data->tokenizer;

//     // Create an array to store child process IDs
//     pid_t child_pids[nb];

//     while (i < nb)
//     {
//         while (curr && curr->type != PIPE)
//         {
//             if (curr->type == CMD)
//             {
//                 cmd = ft_split(curr->content, ' ');
//                 cmd_name = get_absolute_path(cmd[0]);
//                 break;
//             }
//             curr = curr->next->next;
//         }

//         if (i != (nb - 1))
//         {
//             curr = curr->next->next;
//             pipe(pipe_fd);
//         }

//         pid = fork();

//         if (pid < 0)
//         {
//             perror("error:");
//             exit(EXIT_FAILURE);
//         }
//         else if (pid == 0)
//         {
//             if (i < (nb - 1))
//             {
//                 dup2(pipe_fd[1], STDOUT_FILENO);
//                 close(pipe_fd[1]);
//             }
//             if (i > 0)
//             {
//                 dup2(prev_in, STDIN_FILENO);
//             }

//             // Close all pipe file descriptors in the child process
//             close(pipe_fd[0]);
//             setup_redirections(data->tokenizer);

//             if (cmd_name)
//             {
//                 execve(cmd_name, cmd, data->env);
//                 perror("execve error: ");
//                 exit(EXIT_FAILURE);
//             }
//             else
//             {
//                 fprintf(stderr, "Command not found: %s\n", cmd[0]);
//                 exit(EXIT_FAILURE);
//             }
//         }
//         else
//         {
//             if (i < nb - 1)
//                 close(pipe_fd[1]);

//             if (i > 0)
//                 close(prev_in);

//             prev_in = pipe_fd[0];
//         }

//         // Store the child process ID in the array
//         child_pids[i] = pid;

//         i++;
//     }

//     // Wait for all child processes to finish
//     for (i = 0; i < nb; i++)
//     {
//         waitpid(child_pids[i], NULL, 0);
//     }
// }


// void	execute_compound_command(t_data *data)
// {
// 	char	**cmd;
// 	char	*cmd_name;
// 	int		i;
// 	int		cmd_nbr;
// 	int		p1[2];
// 	int		p2[2];
// 	pid_t	pid;

// 	i = 0;
// 	cmd_name = NULL;
// 	cmd_nbr = count_cmds(data->tokenizer);
// 	pipe(p1);
// 	pipe(p2);
// 	while (i < cmd_nbr)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			setup_pipes(p1, p2, i, cmd_nbr);
// 			setup_redirections(data->tokenizer);
// 			exec_cmd(data, cmd, cmd_name);
// 		}
// 		setup_nchild_pipes(p1, p2, i);
// 		i++;
// 	}
// 	close_all_pipes(p1, p2);
// 	waitpid(pid, 0, 0);
// }

// void	setup_pipes(int *p1, int *p2, int i, int cmd_nbr)
// {
// 	if (i == 0)
// 	{
// 		dup2(p1[1], STDIN_FILENO);
// 		close(p1[0]);
// 		close(p2[0]);
// 		close(p2[1]);
// 	}
// 	if (i % 2)
// 	{
// 		dup2(p2[1], p1[0]);
// 		close(p1[1]);
// 		close(p2[0]);
// 	}
// 	if (i % 2 == 0)
// 	{
// 		dup2(p1[1], p2[0]);
// 		close(p1[0]);
// 		close(p2[1]);
// 	}
// 	if (i == cmd_nbr)
// 	{
// 		if (i % 2 == 0)
// 		{
// 			dup2(STDOUT_FILENO, p2[0]);
// 			close(p1[0]);
// 			close(p1[1]);
// 			close(p2[1]);
// 		}
// 		if (i % 2)
// 		{
// 			dup2(STDOUT_FILENO, p1[0]);
// 			close(p1[1]);
// 			close(p2[0]);
// 			close(p2[1]);
// 		}
// 	}
// }

// void	close_all_pipes(int *p1, int *p2)
// {
// 	close(p1[0]);
// 	close(p1[1]);
// 	close(p2[0]);
// 	close(p2[1]);
// }

// void	setup_nchild_pipes(int *p1, int *p2, int i)
// {
// 	if (i % 2 == 0)
// 	{
// 		close(p2[0]);
// 		close(p2[1]);
// 		pipe(p2);
// 	}
// 	else
// 	{
// 		close(p1[0]);
// 		close(p1[1]);
// 		pipe(p1);
// 	}
// }
