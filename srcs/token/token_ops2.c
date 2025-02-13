/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_lless(t_minishell *minishell, int *i)
{
	if (!ft_create_hdoc_token(minishell))
		return (ft_free_token_list(minishell), false);
	*i += 2;
	return (true);
}

static bool	ft_handle_pipe_token(t_minishell *minishell, char *input, int *i)
{
	if (input[*i] == '|')
		return (ft_pipe(minishell, i));
	return (true);
}

static bool	ft_handle_great_token(t_minishell *minishell, char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (ft_ggreat(minishell, i));
	else if (input[*i] == '>')
		return (ft_great(minishell, i));
	return (true);
}

static bool	ft_handle_less_token(t_minishell *minishell, char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
		return (ft_lless(minishell, i));
	else if (input[*i] == '<')
		return (ft_less(minishell, i));
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
		else if (input[i] == '>')
		{
			if (!ft_handle_great_token(minishell, input, &i))
				return (false);
		}
		else if (input[i] == '<')
		{
			if (!ft_handle_less_token(minishell, input, &i))
				return (false);
		}
		else if (!ft_word(minishell, input, &i))
			return (false);
	}
	return (true);
}
