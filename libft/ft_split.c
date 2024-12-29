/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:00:50 by aistierl          #+#    #+#             */
/*   Updated: 2024/06/10 17:35:16 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	word_count(const char *s, char c)
{
	int				count;
	unsigned int	i;

	if (s[0] == '\0')
		return (0);
	count = 0;
	i = 0;
	if (ft_strchr(s, c) == NULL && c != '\0')
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_duparray(const char *s, unsigned int start, unsigned int end)
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

static char	**ft_get_free(char **tab, unsigned int index)
{
	while (index > 0)
	{
		free(tab[--index]);
	}
	free(tab);
	return (NULL);
}

static char	**ft_fill_tab(const char *s, char c, char **tab)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;

	i = 0;
	j = 0;
	start = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			start = i + 1;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			tab[j] = ft_duparray(s, start, (i + 1));
			if (tab[j] == NULL)
				return (ft_get_free(tab, j));
			j++;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	split = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (split == NULL || s == NULL)
	{
		free(split);
		return (NULL);
	}
	return (ft_fill_tab(s, c, split));
}
