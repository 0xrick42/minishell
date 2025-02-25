/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:37:56 by aistierl          #+#    #+#             */
/*   Updated: 2025/02/25 18:56:12 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_word_count_quotes(char *s)
{
	int				count;
	unsigned int	i;

	count = 1;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '"' && s[i] != '\'')
				i++;
		}
		if (s[i] == ' ' && s[i + 1] != ' ')
			count++;
		i++;
	}
	return (count);
}

char	*ft_duparray_quotes(char *s, int start, int end)
{
	char			*mem_word;
	unsigned int	i;

	mem_word = malloc((end - start) + 1);
	if (mem_word == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		mem_word[i] = s[start];
		i++;
		start++;
	}
	mem_word[i] = '\0';
	return (mem_word);
}

static char	**ft_fill_tab_quotes(char *s, char **tab)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (s[i] != '\0')
	{
        if (s[i] == '"' || s[i] == '\'')
            ft_skip_quotes(s, &i);
		if (s[i] == ' ')
			start = i + 1;
		if (s[i] != ' ' && (s[i + 1] == ' ' || s[i + 1] == '\0'))
		{
			tab[j] = ft_duparray_quotes(s, start, (i + 1));
			if (tab[j] == NULL)
				return (ft_get_free(tab, j));
			j++;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split_quotes(char *s)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_word_count_quotes(s) + 1));
	if (split == NULL)
		return (NULL);
	split = ft_fill_tab_quotes(s, split);
	return (split);
}