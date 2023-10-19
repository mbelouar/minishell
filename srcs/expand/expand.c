/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrital- <mrital-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:21:44 by mrital-           #+#    #+#             */
/*   Updated: 2023/10/19 16:15:50 by mrital-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_mini_expen(t_tokenizer *token, char **env)
// {
// 	t_tokenizer	*cmd;

// 	cmd = token;
// 	while (cmd)
// 	{
// 		cmd->content = get_expand(cmd->content, env);
// 		cmd = cmd->next;
// 	}
// }

char	*get_expand(char *content, char **env)
{
	int		len;
	char	*str;

	len = get_str_len(content, env);
	str = get_new_string(len, content, env);
	// free(content);
	return (ft_remove_quotes(str));
}

int	get_str_len(char *data, char **env)
{
	t_tokenizer	s;

	s.i = 0;
	s.len = 0;
	while (data[s.i])
	{
		if (data[s.i] && data[s.i] != '\'')
		{
			s.len++;
			s.i++;
		}
		else if (data[s.i] == '$' && ++s.i)
			ft_get_len(&s, data, env);
		else
		{
			s.len++;
			s.i++;
		}
	}
	return (s.len);
}

void	ft_get_len(t_tokenizer *token, char *data, char **env)
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

// void	expand(t_data *data)
// {
// 	t_tokenizer	*cmd;

// 	if (!data)
// 		return ;
// 	cmd = data->tokenizer;
// 	while (cmd)
// 	{
// 		ft_mini_expen(cmd, data->env);
// 		cmd = cmd->next;
// 	}
// }
