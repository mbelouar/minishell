/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrital- <mrital-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:21:41 by mrital-           #+#    #+#             */
/*   Updated: 2023/10/20 12:08:10 by mrital-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_new_string(int len, char *content, char **env)
{
	t_list	*token;
	char		*str;

	token = (t_list *)malloc(sizeof(t_list));
	token->dup = calloc(len + 1, sizeof(char));
	token->i = 0;
	token->check = 0;
	token->len = 0;
	while (content[token->i])
	{
		if (content[0] == '\'' && ++token->i)
			ft_go(token, content);
		else if (content[token->i] == '$' && ++token->i)
			ft_help_get_str(content, token, env);
		else
		{
			token->dup[token->len] = content[token->i];
			token->len++;
			token->i++;
		}
	}
	token->dup[token->len] = '\0';
	str = ft_free_new_str(token);
	return (str);
}

void	ft_help_get_str(char *content, t_list *token, char **env)
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
		if (ft_hundling(token, content, str, env) == 1)
			return ;
	}
	if (str)
		free(str);
}

void	ft_go(t_list *token, char *content)
{
	token->dup[token->len] = '\'';
	token->len++;
	while (content[token->i] && content[token->i] != '\'')
	{
		token->dup[token->len] = content[token->i];
		token->len++;
		token->i++;
	}
	token->dup[token->len] = '\'';
}

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

int	ft_hundling(t_list *s, char *data, char *string, char **env)
{
	s->identify = get_index(&data[s->i]);
	s->var = get_var(s->identify, env);
	if (s->identify[0] == '?' && s->identify[1] == '\0')
	{
		string = ft_itoa(g_status);
		s->var = ft_strdup(string);
		s->to_free = 1;
		// free(string);
	}
	if (!s->var)
	{
		s->check = 1;
		// free(s->identify);
		return (1);
	}
	s->i = s->i + ft_strlen(s->identify);
	char *tem = s->dup;
	s->dup = malloc(ft_strlen(s->var) + ft_strlen(tem) + 1);
	ft_memcpy(s->dup, tem, ft_strlen(tem));	
	ft_memcpy(&s->dup[s->len], s->var, ft_strlen(s->var));
	s->len = s->len + ft_strlen(s->var);
	free(s->identify);
	if (s->to_free == 1)
		free(s->var);
	return (0);
}
