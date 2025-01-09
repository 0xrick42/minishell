/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:30:09 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/09 13:48:42 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_notword(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
}

bool	ft_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	return (false);
}

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
		return (ft_error("Unclosed quotes."), false);
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
			|| !ft_strncmp(input, "||", 2))
		{
			ft_error("Not handling the following characters:");
			return (ft_error("\\, ;, (), {}, &, &&, ||, *"), false);
		}
		i++;
	}
	return (true);
}

int	ft_wordlen(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i] && !ft_space(input[i]) && !ft_notword(input[i]))
	{
		if (input[0] == '\"' || input[0] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\"' && input[i] != '\'')
			{
				i++;
				count++;
			}
			break ;
		}
		i++;
		count++;
	}
	return (count);
}
