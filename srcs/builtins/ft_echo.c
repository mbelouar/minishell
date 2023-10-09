/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:29 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/09 20:58:38 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	while (s[i])
	{
		if (s[i] != 34 && s[i] != 39)
		{
			res[j] = s[i];
			j++;
		}
		i++;
	}
	return (res);
}

void	ft_echo(char **args)
{
	char	*arg;
	int		i;
	int		n;

	i = 1;
	n = 0;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
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
