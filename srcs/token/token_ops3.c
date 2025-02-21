/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:30:42 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/28 18:15:33 by ykhomsi         ###   ########.fr       */
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
