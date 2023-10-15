/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:40:52 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/15 20:41:37 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;
	}
}

void	signal_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 1;
		exit(1);
	}
}
