/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:29 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/15 00:55:44 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	fill_new_str(char *s, char *res, int *i, int *j)
{
	while (s[*i])
	{
		if (s[*i] != 34 && s[*i] != 39)
		{
			res[*j] = s[*i];
			(*j)++;
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
		if (s[i] != 34 && s[i] != 39)
			len++;
		i++;
	}
	res = ft_calloc(len, sizeof(char));
	i = 0;
	j = 0;
	fill_new_str(s, res, &i, &j);
	return (res);
}

void	ft_echo(char **args)
{
	int		i;
	int		n;

	i = 1;
	n = 0;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		if (args[i][2] != 'n' && args[i][2] != '\0')
		{
			n = 0;
			break ;
		}
		n++;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
}
