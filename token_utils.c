/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:53:48 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/09 13:19:18 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token_list(t_minishell *minishell)
{
	t_token	*current_token;
	t_token	*tmp;

	current_token = minishell->token_list;
	while (current_token)
	{
		tmp = current_token->next_token;
		free(current_token->token_name);
		free(current_token);
		current_token = tmp;
	}
	return ;
}

void	ft_append_token(t_minishell *minishell, t_token *new_token)
{
	t_token	*current_token;

	if (minishell->token_list == NULL)
	{
		new_token->token_id = 0;
		minishell->token_list = new_token;
	}
	else
	{
		current_token = minishell->token_list;
		while (current_token->next_token != NULL)
			current_token = current_token->next_token;
		new_token->token_id = current_token->token_id + 1;
		current_token->next_token = new_token;
	}
	return ;
}
