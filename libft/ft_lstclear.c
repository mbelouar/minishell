/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:45:46 by mbelouar          #+#    #+#             */
/*   Updated: 2022/10/15 17:25:16 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*p;

	if (!lst)
		return ;
	while (*lst)
	{
		p = *lst;
		*lst = (*lst)->next;
		free(p->content);
		free(p);
	}
	*lst = NULL;
}
