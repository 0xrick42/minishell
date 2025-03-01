/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:15:22 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/29 01:35:45 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_create_hdoc_token(t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
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
	int		len;

	len = ft_wordlen(input);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->token_id = ft_last_token_id(minishell) + 1;
	new_token->token_name = ft_substr(input, 0, len);
	new_token->token_type = WORD;
	new_token->token_redir = NONE;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}
