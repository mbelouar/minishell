/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:53:00 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/12 20:05:27 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_pipe_struct(t_pipe *p)
{
	if (p->cmd_name)
	{
		free(p->cmd_name);
		p->cmd_name = NULL;
	}
	if (p->cmd)
		free_double_pointer(p->cmd);
}

void	execute_compound_command(t_data *data)
{
	int			i;
	t_pipe		p;
	t_tokenizer	*curr;
	int			*child_pids;

	i = 0;
	p.prev_in = 0;
	p.cmd_name = NULL;
	p.cmd_nb = count_cmds(data->tokenizer);
	child_pids = ft_calloc(p.cmd_nb, sizeof(int));
	curr = data->tokenizer;
	while (i < p.cmd_nb)
	{
		while (curr)
		{
			if (curr->type == PIPE)
			{
				curr = curr->next;
				continue ;
			}
			if (curr->type == CMD)
			{
				p.cmd = ft_split(curr->content, ' ');
				p.cmd_name = get_absolute_path(p.cmd[0], data);
				break ;
			}
			else if (curr->type == BUILTIN)
			{
				p.cmd = ft_split(curr->content, ' ');
				break ;
			}
			curr = curr->next;
		}
		if (i != (p.cmd_nb - 1))
			pipe(p.pipe_fd);
		p.pid = fork();
		if (p.pid < 0)
			perror_fork();
		else if (p.pid == 0)
			child_exec(data, p, i, curr);
		else
		{
			if (i < p.cmd_nb - 1)
				close(p.pipe_fd[1]);
			if (i > 0)
				close(p.prev_in);
			p.prev_in = p.pipe_fd[0];
		}
		if (curr->type == CMD || curr->type == BUILTIN)
			curr = curr->next;
		free_pipe_struct(&p);
		child_pids[i] = p.pid;
		i++;
	}
	i = -1;
	while (++i < p.cmd_nb)
		waitpid(child_pids[i], NULL, 0);
	free(child_pids);
}
