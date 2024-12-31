/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:30:09 by aistierl          #+#    #+#             */
/*   Updated: 2024/12/31 19:34:10 by aistierl         ###   ########.fr       */
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

int	ft_wordlen(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i] && !ft_space(input[i]) && !ft_notword(input[i]))
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\"' && input[i] != '\'')
			{
				i++;
				count++;
			}
			if (!input[i])
				return (-1);
			break ;
		}
		i++;
		count++;
	}
	return (count);
}
