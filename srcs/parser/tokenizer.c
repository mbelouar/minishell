/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 03:22:02 by mrital-           #+#    #+#             */
/*   Updated: 2023/10/23 16:32:33 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_init(t_n *n)
{
	n->content = NULL;
	n->str = NULL;
	n->tmp = NULL;
	n->test = NULL;
}

static void	ft_pipe(t_data *data, char *str)
{
	str = ft_strdup("|");
	ft_create_node(&data->tokenizer, str, PIPE);
	free(str);
	str = NULL;
}

static void	ft_ft(t_n *n, t_type type, t_data *data)
{
	n->content = ft_strtrim(n->content, " ");
	n->tmp = ft_split(n->content, ' ');
	if (builtin_check(n->tmp[0]))
		type = BUILTIN;
	else
		type = CMD;
	free_double_pointer(n->tmp);
	n->test = get_expand(data, n->content, data->env);
	ft_create_node(&data->tokenizer, n->test, type);
	free(n->content);
	free(n->test);
	n->content = NULL;
}

static void	ft_doppage(t_n *n, t_list **curr)
{
	n->content = ft_strdup("");
	while (*curr)
	{
		n->content = ft_strjoin(n->content, (*curr)->content);
		n->content = ft_strjoin(n->content, " ");
		if ((*curr)->next && ((*curr)->next->content[0] == '|'
				|| (*curr)->next->content[0] == '<'
				|| (*curr)->next->content[0] == '>'))
			break ;
		(*curr) = (*curr)->next;
	}
}

void	tokenizer(t_data *data)
{
	t_list	*curr;
	t_type	type;
	t_n		n[1];

	type = 0;
	ft_init(n);
	curr = data->lst;
	while (curr)
	{
		if (curr->content[0] == '<' || curr->content[0] == '>')
		{
			ft_redirection(curr, data);
			curr = curr->next;
		}
		else if (curr->content[0] == '|')
			ft_pipe(data, n->str);
		else
		{
			ft_doppage(n, &curr);
			ft_ft(n, type, data);
		}
		if (curr == NULL)
			break ;
		curr = curr->next;
	}
}
