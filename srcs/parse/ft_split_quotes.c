/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 09:15:22 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/26 11:42:15 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_handle_quoted_word(const char *s, int *i);
bool	ft_process_word(char **split, char const *s, char c, int pos[2]);

static int	ft_count_words(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			if (s[i] == '"' || s[i] == '\'')
				count += ft_handle_quoted_word(s, &i) - 1;
			else
				while (s[i] && s[i] != c)
					i++;
		}
	}
	return (count);
}

static bool	ft_init_split(char const *s, char c, char ***split, int *words)
{
	if (!s)
		return (false);
	*words = ft_count_words(s, c);
	*split = (char **)malloc(sizeof(char *) * (*words + 1));
	if (!*split)
		return (false);
	return (true);
}

static bool	ft_process_all_words(char **split, char const *s, char c, int words)
{
	int	pos[2];

	pos[0] = 0;
	pos[1] = 0;
	while (pos[1] < words)
	{
		if (!ft_process_word(split, s, c, pos))
		{
			ft_free_split(split, pos[1]);
			return (false);
		}
	}
	return (true);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**split;
	int		words;

	if (!ft_init_split(s, c, &split, &words))
		return (NULL);
	if (!ft_process_all_words(split, s, c, words))
		return (NULL);
	split[words] = NULL;
	return (split);
}
