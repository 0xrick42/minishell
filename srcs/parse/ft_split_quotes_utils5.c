/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils5.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:05:18 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/26 23:15:42 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_quoted_word(const char *s, int *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i])
		(*i)++;
	return (1);
}

bool	ft_process_word(char **split, char const *s, char c, int pos[2])
{
	while (s[pos[0]] && s[pos[0]] == c)
		pos[0]++;
	if (s[pos[0]])
	{
		if (s[pos[0]] == '"' || s[pos[0]] == '\'')
			split[pos[1]] = ft_get_quoted_word(s, &pos[0]);
		else
			split[pos[1]] = ft_get_normal_word(s, c, &pos[0]);
		if (!split[pos[1]])
			return (false);
		pos[1]++;
	}
	return (true);
}
