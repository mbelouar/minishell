/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrital- <mrital-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:21:44 by mrital-           #+#    #+#             */
/*   Updated: 2023/10/20 15:53:42 by mrital-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char	*get_expand(char *content, char **env)
{
	int		len;
	char	*str;
	char	*temp;

	len = get_str_len(content, env);
	str = get_new_string(len, content, env);
	temp = ft_remove_quotes(str);
	//  printf("=========%p=========\n",temp);
	free(str);
	// free(content);
	return (temp);
}

int	get_str_len(char *token, char **env)
{
	t_list	s;

	s.i = 0;
	s.len = 0;
	while (token[s.i])
	{
		if (token[s.i] && token[s.i] != '\'')
		{
			s.len++;
			s.i++;
		}
		else if (token[s.i] == '$' && ++s.i)
			ft_get_len(&s, token, env);
		else
		{
			s.len++;
			s.i++;
		}
	}
	return (s.len);
}

void	ft_get_len(t_list *token, char *data, char **env)
{
	if (ft_valid(data[token->i]) == 0)
		token->len++;
	else
	{
		token->id = get_index(&data[token->i]);
		token->var = get_var(token->id, env);
		if (!token->var)
		{
			free(token->id);
			return ;
		}
		token->i = token->i + ft_strlen(token->id);
		token->len = token->len + ft_strlen(token->var);
		free(token->id);
	}
}

