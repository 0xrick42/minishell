/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_quoted_word(char const *s, int *i)
{
	char	*word;
	int		len;
	char	quote;

	quote = s[*i];
	(*i)++;
	len = 0;
	while (s[*i + len] && s[*i + len] != quote)
		len++;
	word = ft_substr(s, *i, len);
	*i = *i + len + 1;
	return (word);
}

char	*ft_get_normal_word(char const *s, char c, int *i)
{
	char	*word;
	int		len;

	len = 0;
	while (s[*i + len] && s[*i + len] != c)
		len++;
	word = ft_substr(s, *i, len);
	*i = *i + len;
	return (word);
}

char	*ft_get_word(char const *s, char c, int *i)
{
	if (s[*i] == '"' || s[*i] == '\'')
		return (ft_get_quoted_word(s, i));
	return (ft_get_normal_word(s, c, i));
}
