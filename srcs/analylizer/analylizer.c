/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analylizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:44:04 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/09 17:50:38 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int analylizer_pipe(t_data *data)
// {
// 	t_list *tokens;
//     int ft;

//     ft = 1;
//     tokens = data->lst;
//     while (tokens)
//     {
//         if (tokens->content)
//         {
//             if (ft && tokens->content[0] == '|')
//                 return 4;
//             if (tokens->content[0] == '|' && tokens->content[1] == '|'
//             && tokens->content[2] == '|')
//                 return 1;
//             if (tokens->next)
//             {
//                 if (tokens->content[0] == '|' && tokens->next->content[0] == '\0')
//                     return 4;
//             }
//             else
//             {
//                 if (tokens->content[0] == '|')
//                     return (4);
//             }
//         }
//         tokens = tokens->next;
//         ft = 0;
//     }
//     return 0;
// }


// int analylizer_redi(t_data	*data)
// {
// 	t_list *tokens = data->lst;
//     t_list *current = tokens;
//     t_list *prev = NULL;

//     while (current)
//     {
//         if (current->content)
//         {
//             if (current->content[0] == '>' && current->content[1] == '>'
//             && current->content[2] == '>')
//                 return 3;
//             if ((current->content[0] == '>' || current->content[0] == '<')
//             && (current->next == NULL || current->next->content[0] == '\0'
//             || (current->next->content[0] == '>'
//             || current->next->content[0] == '<')))
//                 return 2;
//         }

//         prev = current;
//         current = current->next;
//     }
//     return 0;
// }

int	analylizer(t_list *list)
{
    int pipe;
    t_list  *curr;

    curr = list;
    while(curr)
    {
        pipe = *curr->content == '|';
        if(*curr->content == '|' || *curr->content == '<' || *curr->content == '>')
        {
            if (ft_strlen(curr->content) > 2)
                return (1);
            else if (!curr->next)
                return (1);
            else if (ft_strchr("<|>", *(curr->next->content)) && !pipe)
                return (1);
            else if (ft_strchr("|", *(curr->next->content)) && pipe)
                return (1);
        }
        curr = curr->next;
    }
	return (0);
}

int check_quotes(char* line)
{
    int q = 0;
    int i = 0;
    int type = 0;

    while(line[i])
    {
        if ((type == 0 && q == 0)
        && (line[i] == 34 ||  line[i] == 39))
        {
            type = line[i++];
            q++;
        }
        if (line[i] == type)
        {
            q++;
            i++;
        }
        if (q == 2 && (line[i] == 34 ||  line[i] == 39))
        {
            type = line[i];
            q = 1;
            i++;
        }
        i++;
    }
    if (q % 2 == 0)
        return (1);
    return (0);
}
