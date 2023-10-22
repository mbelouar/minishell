/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:23:12 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/22 19:12:35 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_quotes_err(t_data *data, char *line)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	free_token_list(&data->tokenizer);
	ft_lstclear(&data->lst);
	free(line);
}

void	ft_syntax_err(t_data *data, char *line, t_list *lst)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
	free_token_list(&data->tokenizer);
	ft_lstclear(&data->lst);
	ft_lstclear(&lst);
	free(line);
}

char	*ft_readline(t_data *data)
{
	char	*line;

	line = readline("friw-kriw@ ");
	if (!line)
		end_of_file(data);
	else
		add_history(line);
	return (line);
}
