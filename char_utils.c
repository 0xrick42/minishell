/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:30:09 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/24 19:36:24 by aistierl         ###   ########.fr       */
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
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (input[i] && !ft_space(input[i]) && !ft_notword(input[i]))
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			if (i != 0)
				flag = 1;
			i++;
			while (input[i] && input[i] != '\"' && input[i] != '\'')
				i++;
			if (ft_space(input[i + 1]) || !input[i + 1])
			{
				if (flag == 1)
					return (i + 1);
				return (i - 1);
			}
		}		
		i++;
	}
	return (i);
}
