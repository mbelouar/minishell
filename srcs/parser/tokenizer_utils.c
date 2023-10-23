/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:28:00 by mrital-           #+#    #+#             */
/*   Updated: 2023/10/23 16:17:40 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_token_list(t_tokenizer **lst)
{
	t_tokenizer	*p;

	if (!lst)
		return ;
	while (*lst)
	{
		p = *lst;
		*lst = (*lst)->next;
		free(p->content);
		free(p);
	}
	*lst = NULL;
}

void	free_double_pointer(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	fill_new_str(char *s, char *res, int *i, int *j)
{
	int		inside_quotes;
	char	quote;

	inside_quotes = 0;
	quote = '\0';
	while (s[*i])
	{
		if (inside_quotes)
		{
			if (s[*i] == quote)
				inside_quotes = ((quote = '\0')) * 0;
			else
				res[(*j)++] = s[*i];
		}
		else
		{
			if (s[*i] == '\"' || s[*i] == '\'')
				inside_quotes = ((quote = s[*i])) * 0 + 1;
			else
				res[(*j)++] = s[*i];
		}
		(*i)++;
	}
}

char	*ft_remove_quotes(char *s)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != '\"' && s[i] != '\'')
			len++;
		i++;
	}
	res = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	j = 0;
	fill_new_str(s, res, &i, &j);
	res[j] = '\0';
	return (res);
}
