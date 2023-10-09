/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:30:29 by mbelouar          #+#    #+#             */
/*   Updated: 2023/10/09 17:42:32 by mbelouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

static t_list *ft_array_to_lst(char **arr)
{
	int		i;
	t_list	*lst;
	t_list	*node;

	lst = NULL;
	node = NULL;
	i = -1;
	while (arr[++i])
	{
		node = ft_lstnew(arr[i]);
		if (node == NULL)
			return (NULL);
		ft_lstadd_back(&lst, node);
	}
	for (int i = 0; arr[i]; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
	return (lst);
}

static int ft_count_words(char const *s)
{
	int	i;
	int	cnt;
	int quote;
	int 	token;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i])
			cnt++;
		if (ft_strchr("<>|",s[i]) && s[i])
		{
			token = s[i++];
			while (s[i] == token)
				++i;
		}
		else
		{
			while(!ft_strchr("<|>",s[i]) && s[i] && s[i] != ' ')
			{
				quote = 0;
				if (s[i] == 34 || s[i] == 39)
					quote = s[i++];
				while (quote && s[i] != quote)
					i++;
				++i;
			}
		}
	}
	return (cnt);
}

static void	fill_s(char **dest, char const *s, char c, int words_nbr)
{
	int	i;
	int	j;
	int quote;
	int token;

	(void)c;
	j = 0;
	while (j < words_nbr)
	{
		i = 0;
		while (*s && *s == ' ')
			++s;
			if (ft_strchr("<>|",s[i]) && s[i])
			{
				token = s[i++];
				while (s[i] == token)
					++i;
			}
			else
			{
				while(!ft_strchr("<|>",s[i]) && s[i] && s[i] != ' ')
				{
					quote = 0;
					if (s[i] == 34 || s[i] == 39)
						quote = s[i++];
					while (quote && s[i] != quote)
						i++;
					++i;
				}
			}
			//
			dest[j] =ft_substr(s, 0, i);
		// }
		j++;
		s += i;
	}
	dest[j] = NULL;
}

t_list *ft_split_lst(char const *s, char c)
{
	//
	char	**dest;
	int		count_word;

	if (!s)
		return (NULL);
	count_word = ft_count_words(s);
	dest = malloc(sizeof(char *) * (count_word + 1));
	if (!dest)
		return (NULL);
	fill_s(dest, s, c, count_word);
	return (ft_array_to_lst(dest));
}
