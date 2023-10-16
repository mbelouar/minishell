/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:37:50 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/16 22:58:00 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_valid(char c)
{
	return ((ft_isalnum(c)) || (c == '_') || (c = '?'));
}

char	*get_index(char *string)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (string[i] >= '0' && string[i] <= '9')
	{
		while (string[i] && (string[i] >= '0' && string[i] <= '9'))
			i++;
		j = i;
		while (string[j] && !ft_isdigit(string[i]))
			j++;
		return (ft_substr(string, i, j));
	}
	i = 0;
	if (string[i] && string[i] == '?')
		return (ft_substr(string, 0, i + 1));
	while (string[i] && (ft_isalnum(string[i]) || (string[i] == '?')))
		i++;
	return (ft_substr(string, 0, i));
}

char	*get_var(char *id, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] == id[j] && id[j] != '\0')
			j++;
		if (env[i][j] == '=' && id[j] == '\0')
			return (&env[i][j + 1]);
		i++;
	}
	return (NULL);
}
