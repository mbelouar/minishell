/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrital- <mrital-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:29 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/19 18:48:12 by mrital-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#include <stdio.h>
#include <stdlib.h>

static void fill_new_str(char *s, char *res, int *i, int *j) {
    int inside_quotes = 0;
    char quote = '\0';

    while (s[*i]) {
        if (inside_quotes) {
            if (s[*i] == quote) {
                inside_quotes = 0;
                quote = '\0';
            } else {
                res[(*j)++] = s[*i];
            }
        } else {
            if (s[*i] == '"' || s[*i] == '\'') {
                inside_quotes = 1;
                quote = s[*i];
            } else {
                res[(*j)++] = s[*i];
            }
        }
        (*i)++;
    }
}

char *ft_remove_quotes(char *s) {
    char *res;
    int len;
    int i;
    int j;

    i = 0;
    len = 0;
    while (s[i]) {
        if (s[i] != '"' && s[i] != '\'') {
            len++;
        }
        i++;
    }
    res = (char *)malloc((len + 1) * sizeof(char));
    i = 0;
    j = 0;
    fill_new_str(s, res, &i, &j);
    res[j] = '\0';
    return res;
}

// static void	fill_new_str(char *s, char *res, int *i, int *j)
// {
// 	while (s[*i])
// 	{
// 		if (s[*i] != 34 && s[*i] != 39)
// 		{
// 			res[*j] = s[*i];
// 			(*j)++;
// 		}
// 		(*i)++;
// 	}
// }

// char	*ft_remove_quotes(char *s)
// {
// 	char	*res;
// 	int		len;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	len = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != 34 && s[i] != 39)
// 			len++;
// 		i++;
// 	}
// 	res = ft_calloc(len, sizeof(char));
// 	i = 0;
// 	j = 0;
// 	fill_new_str(s, res, &i, &j);
// 	res[j] = '\0';
// 	return (res);
// }

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
