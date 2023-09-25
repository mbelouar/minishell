/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:47:48 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/24 18:48:23 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_cmds(t_tokenizer *lst)
{
	t_tokenizer	*curr;
	int			i;

	curr = lst;
	i = 0;
	while (curr)
	{
		if (curr->type == CMD)
			i++;
		curr = curr->next;
	}
	return (i);
}

int	check_pipe(t_tokenizer *lst)
{
	t_tokenizer	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->content[0] == '|')
			return (1);
		curr = curr->next;
	}
	return (0);
}
