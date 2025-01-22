/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:37:12 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/22 13:19:27 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_error(char *error_message)
{
	printf("Minishell: syntax error near unexpected token");
	printf(" '%s'\n", error_message);
	return ;
}

bool	ft_check_pipe(t_minishell *minishell)
{
	t_token	*current;

	current = minishell->token_list;
	while (current)
	{
		if (current->token_type == PIPE)
		{
			if (current->token_id == 0 && !current->next_token)
				return (ft_token_error(current->token_name), false);
			else if (current->token_id == 0 || !current->next_token)
				return (ft_token_error(current->token_name), false);
			else if (current->next_token->token_type == PIPE)
				return (ft_token_error(current->token_name), false);
			else if (current->next_token->token_redir == REDIR)
				return (ft_token_error(current->token_name), false);
		}
		current = current->next_token;
	}
	return (true);
}

bool	ft_check_redir(t_minishell *minishell)
{
	t_token	*current;

	current = minishell->token_list;
	while (current)
	{
		if (current->token_redir == REDIR)
		{			
			if (!current->next_token)
				return (ft_token_error("newline"), false);
			else if (current->next_token->token_type == PIPE)
				return (ft_token_error("|"), false);
			else if (current->next_token->token_redir == REDIR)
				return (ft_token_error(current->token_name), false);
			else if (current->token_id == ft_last_token_id(minishell) - 1
				&& current->next_token->token_redir == REDIR)
				return (ft_token_error(current->next_token->token_name), false);
		}
		current = current->next_token;
	}
	return (true);
}
