/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:28:00 by mrital-           #+#    #+#             */
/*   Updated: 2023/10/23 17:00:29 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_free_new_str(t_list *s)
{
	char	*string;

	if (s->check)
	{
		free(s->dup);
		free(s->identify);
		s->dup = ft_strdup("");
	}
	string = ft_strdup(s->dup);
	free(s->dup);
	free(s);
	return (string);
}

void	ft_help_get_str(t_data *data, char *content,
			t_list *token, char __unused **env)
{
	char	*str;

	str = NULL;
	if (ft_valid(content[token->i]) == 0)
	{
		token->dup[token->len] = content[token->i];
		token->len++;
	}
	else
	{
		if (ft_hundling(data, token, content, str) == 1)
			return ;
	}
	if (str)
		free(str);
}
