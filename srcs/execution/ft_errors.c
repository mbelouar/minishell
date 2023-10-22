/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:21:02 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/22 19:09:59 by mbelouar         ###   ########.fr       */
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

void	err_msg(t_data *data, char *str, int status)
{
	data->exit_status = status;
	ft_putstr_fd(str, 2);
}
