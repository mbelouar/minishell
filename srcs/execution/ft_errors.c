/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:21:02 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/15 23:51:27 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	perror_exec(void)
{
	perror("Error in execve:");
	exit(EXIT_FAILURE);
}

void	perror_fork(void)
{
	perror("Error in fork:");
	exit(EXIT_FAILURE);
}

void	error_sentence(char *str)
{
	ft_putstr_fd(str, 2);
}

