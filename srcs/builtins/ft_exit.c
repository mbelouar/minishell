/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:34 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/21 19:55:59 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args, t_data *data)
{
	if (!args[1])
		exit(0);
	if (!is_number(args[1]))
	{
		error_sentence(data, "exit: numeric argument required\n", 255);
		exit(255);
	}
	else if (is_number(args[1]) && args[2])
		return (error_sentence(data, "exit: too many arguments\n", 1));
	else if (is_number(args[1]))
		exit(ft_atoi(args[1]));
}
