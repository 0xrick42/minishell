/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*ft_handle_dollar(t_minishell *minishell, char *str,
	char *result, int *i)
{
	char	*expanded;

	expanded = ft_expand_dollars(minishell, str, i);
	if (!expanded)
	{
		free(result);
		return (NULL);
	}
	result = ft_join_expanded(result, expanded);
	free(expanded);
	return (result);
}

static char	*ft_handle_char(char *result, char c, int *i)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	result = ft_join_expanded(result, tmp);
	(*i)++;
	return (result);
}

char	*ft_process_string(t_minishell *minishell, char *str)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !ft_in_quotes(str, i))
			result = ft_handle_dollar(minishell, str, result, &i);
		else
			result = ft_handle_char(result, str[i], &i);
		if (!result)
			return (NULL);
	}
	return (result);
}
