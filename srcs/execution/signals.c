/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrital- <mrital-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:40:52 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/18 19:34:18 by mrital-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");//reminder to change 
		rl_on_new_line();
		// rl_replace_line("", 0);
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
