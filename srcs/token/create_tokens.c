/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:25:15 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/28 21:40:22 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_create_pipe_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->token_name = ft_strdup("|");
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = PIPE;
	new_token->token_redir = NONE;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}

bool	ft_create_output_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->token_name = ft_strdup(">");
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = GREAT;
	new_token->token_redir = REDIR;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}

bool	ft_create_input_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->token_name = ft_strdup("<");
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = LESS;
	new_token->token_redir = REDIR;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}

bool	ft_create_append_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->token_name = ft_strdup(">>");
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = GGREAT;
	new_token->token_redir = REDIR;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}
