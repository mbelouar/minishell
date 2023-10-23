/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:53:00 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/23 00:24:10 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_init(t_data *data, t_norm *n)
{
	n->i = -1;
	n->p.prev_in = 0;
	n->p.cmd_name = NULL;
	n->p.cmd_nb = count_cmds(data->tokenizer);
	n->child_pids = ft_calloc(n->p.cmd_nb, sizeof(int));
	n->curr = data->tokenizer;
}

void	ft_ft(t_norm *n, t_data *data)
{
	if (n->i != (n->p.cmd_nb - 1))
		pipe(n->p.pipe_fd);
	n->p.pid = fork();
	if (n->p.pid < 0)
		perror_fork();
	else if (n->p.pid == 0)
		child_exec(data, n->p, n->i, n->curr);
	else
	{
		if (n->i < n->p.cmd_nb - 1)
			close(n->p.pipe_fd[1]);
		if (n->i > 0)
			close(n->p.prev_in);
		n->p.prev_in = n->p.pipe_fd[0];
	}
	if (n->curr->type == CMD || n->curr->type == BUILTIN)
		n->curr = n->curr->next;
	free_pipe_struct(&(n->p));
	n->child_pids[n->i] = n->p.pid;
}

void	ft_ft2(t_norm *n, t_data *data)
{
	n->i = -1;
	while (++(n->i) < n->p.cmd_nb)
		waitpid(n->child_pids[n->i], &data->exit_status, 0);
	data->exit_status = data->exit_status >> 8;
	free(n->child_pids);
}

void	ft_ft3(t_norm *n, t_data *data)
{
	while (++(n->i) < n->p.cmd_nb)
	{
		while (n->curr)
		{
			if (n->curr->type == PIPE)
			{
				n->curr = n->curr->next;
				continue ;
			}
			if (n->curr->type == CMD)
			{
				n->p.cmd = ft_split(n->curr->content, ' ');
				n->p.cmd_name = get_absolute_path(n->p.cmd[0], data);
				break ;
			}
			else if (n->curr->type == BUILTIN)
			{
				n->p.cmd = ft_split(n->curr->content, ' ');
				break ;
			}
			n->curr = n->curr->next;
		}
		ft_ft(n, data);
	}
}

void	execute_compound_command(t_data *data)
{
	t_norm	n[1];

	ft_init(data, n);
	ft_ft3(n, data);
	ft_ft2(n, data);
}
