/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analylizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:44:04 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/10 00:20:59 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	analylizer(t_list *list)
{
	int		pipe;
	t_list	*curr;

	curr = list;
	while (curr)
	{
		pipe = *curr->content == '|';
		if (*curr->content == '|' || *curr->content == '<'
			|| *curr->content == '>')
		{
			if (ft_strlen(curr->content) > 2)
				return (1);
			else if (!curr->next)
				return (1);
			else if (ft_strchr("<|>", *(curr->next->content)) && !pipe)
				return (1);
			else if (ft_strchr("|", *(curr->next->content)) && pipe)
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	check_quotes(char *line)
{
	int	q;
	int	i;
	int	type;

	q = 0;
	i = 0;
	type = 0;
	while (line[i])
	{
		if ((type == 0 && q == 0) && (line[i] == 34 || line[i] == 39))
		{
			type = line[i++];
			q++;
		}
		if (line[i] == type)
		{
			q++;
			i++;
		}
		if (q == 2 && (line[i] == 34 || line[i] == 39))
		{
			type = line[i];
			q = 1;
			i++;
		}
		i++;
	}
	if (q % 2 == 0)
		return (1);
	return (0);
}
