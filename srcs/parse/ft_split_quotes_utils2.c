/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_skip_quoted_word(char const *s, int *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i])
		(*i)++;
}

static void	ft_skip_normal_word(char const *s, char c, int *i)
{
	while (s[*i] && s[*i] != c)
		(*i)++;
}

int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

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
				ft_skip_quoted_word(s, &i);
			else
				ft_skip_normal_word(s, c, &i);
		}
	}
	return (count);
}
