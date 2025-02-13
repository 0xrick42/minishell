/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_handle_redirection(t_minishell *minishell, char *input, int *i)
{
	if (input[*i] == '>')
		return (ft_handle_great_token(minishell, input, i));
	else if (input[*i] == '<')
		return (ft_handle_less_token(minishell, input, i));
	return (true);
}

bool	ft_tokenization(t_minishell *minishell, char *input, int i)
{
	while (input[i])
	{
		if (ft_space(input[i]))
			i++;
		else if (input[i] == '|')
		{
			if (!ft_handle_pipe_token(minishell, input, &i))
				return (false);
		}
		else if (input[i] == '>' || input[i] == '<')
		{
			if (!ft_handle_redirection(minishell, input, &i))
				return (false);
		}
		else if (!ft_word(minishell, input, &i))
			return (false);
	}
	return (true);
}
