/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:40:24 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/14 18:58:58 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_unclosed_quotes(char *input)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			double_quote++;
		else if (input[i] == '\'')
			single_quote++;
		i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (ft_error("unclosed quotes."), false);
	return (true);
}

bool	ft_not_handling(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '"' && input[i] != '\'')
				i++;
		}
		if (input[i] == '\\' || input[i] == ';' || input[i] == '('
			|| input[i] == '{' || input[i] == '&' || input[i] == '*'
			|| !ft_strncmp(input + i, "||", 2))
		{
			printf("Not handling the following characters: ");
			return (printf("\\, ;, (), {}, &, &&, ||, *\n"), false);
		}
		i++;
	}
	return (true);
}

bool	ft_only_spaces(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (!ft_space(input[i]))
			return (false);
		i++;
	}
	return (true);
}
