/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:29 by mbelouar          #+#    #+#             */
/*   Updated: 2023/09/30 00:10:58 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_remove_quotes(char *s)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != 34)
// 			len++;
// 		i++;
// 	}
// 	char *res = ft_calloc(len, sizeof(char));
// 	i = 0;
// 	int j = 0;
// 	while (s[i])
// 	{
// 	    if (s[i] != 34)
// 	    {
// 	        res[j] = s[i];
// 	        j++;
// 	    }
// 	    i++;
// 	}
// 	free((void*)s);
// 	return (res);
// }

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
		arg = args[i];

		if (ft_strchr(arg, '\"') || ft_strchr(arg, '\''))
			ft_remove_quotes(arg);
		write(1, arg, strlen(arg));
		if (args[(i++) + 1])
			write(1, " ", 1);
	}
	if (n == 0)
		write(1, "\n", 1);
}
