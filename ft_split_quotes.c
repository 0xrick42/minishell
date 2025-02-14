/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:58:36 by aistierl          #+#    #+#             */
/*   Updated: 2025/02/14 16:43:25 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_word_count_quotes(const char *s, char c)
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
		if (s[i] == '"' || s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '"' && s[i] != '\'')
				i++;
		}
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	*ft_duparray_quotes(const char *s, unsigned int start, unsigned int end)
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

char	**ft_get_free(char **tab, unsigned int index)
{
	while (index > 0)
	{
		free(tab[--index]);
	}
	free(tab);
	return (NULL);
}

void	ft_skip_quotes(char *s, int *i)
{
	char	quote_char;
	
	quote_char = '\0';
	quote_char = s[*i];
		*i++;
	while (s[*i] != quote_char)
		*i++;
}

bool	ft_add_segment(char *s, int start, int *i, int *j, char **tab)
{
	tab[*j] = ft_duparray_quotes(s, start, *i);
	if (tab[*j] == NULL)
		return (false);
	return (true);
}

char	**ft_fill_tab_quotes(const char *s, char c, char **tab)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;
	char			quote_char;

	i = 0;
	j = 0;
	start = 0;
	quote_char = '\0';
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
			ft_skip_quotes(s, &i);
		if (s[i + 1] == c || s[i + 1] == '\0')
		{			
			if (s[i + 1] == '\0')
			{	
				tab[j] = ft_duparray_quotes(s, start, i + 1);
				if (tab[j] == NULL)
					return (ft_get_free(tab, j));
				return (tab);
			}
			tab[j] = ft_duparray_quotes(s, start, i);
			if (tab[j] == NULL)
				return (ft_get_free(tab, j));
			j++;
			i += 1;
			while (s[i + 1] == ' ' || s[i + 1] == '\t')
				i++;
			start = i + 1;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_word_count_quotes(s, c) + 1));
	if (split == NULL)
		return (NULL);
	split = ft_fill_tab_quotes(s, c, split);
	return (split);
}
