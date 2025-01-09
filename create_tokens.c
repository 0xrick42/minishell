/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:06:30 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/09 13:19:41 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_create_pipe_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
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
	if (new_token == NULL)
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
	if (new_token == NULL)
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
	if (new_token == NULL)
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

bool	ft_create_hdoc_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (false);
	new_token->token_name = ft_strdup("<<");
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = LLESS;
	new_token->token_redir = REDIR;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}

bool	ft_create_word_token(t_minishell *minishell, char *input)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (false);
	if (input[0] == '"' || input[0] == '\'')
		new_token->token_name = ft_substr(input, 1, ft_wordlen(input));
	else
		new_token->token_name = ft_substr(input, 0, ft_wordlen(input));
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = WORD;
	new_token->token_redir = NONE;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}
