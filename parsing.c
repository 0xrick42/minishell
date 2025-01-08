/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:52 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/08 19:11:23 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *error_message)
{
	printf("Error: %s.\n", error_message);
	return ;
}

bool	ft_word_token(t_token *word_token, char *input)
{
	if (input[0] == '"' || input[0] == '\'')
		word_token->token_name = ft_substr(input, 1, ft_wordlen(input));
	else
		word_token->token_name = ft_substr(input, 0, ft_wordlen(input));
	return (true);
}

bool	ft_create_token(t_minishell *minishell, char *input, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	if (type == PIPE || type == GREAT || type == LESS)
		new_token->token_name = ft_substr(input, 0, 1);
	else if (type == GREATGREAT || type == LESSLESS)
		new_token->token_name = ft_substr(input, 0, 2);
	else if (type == WORD)
	{
		if (!ft_word_token(new_token, input))
			return (free(new_token), false);
	}
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = type;
	new_token->token_redir = ft_token_redir(type);
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}

bool	ft_token(t_minishell *minishell, char *input, int *i,
		t_token_type token_type)
{
	if (!ft_create_token(minishell, input + *i, token_type))
		return (ft_free_token_list(minishell), false);
	if (token_type == PIPE || token_type == GREAT || token_type == LESS)
		*i += 1;
	else if (token_type == GREATGREAT || token_type == LESSLESS)
		*i += 2;
	else if (token_type == WORD)
	{
		if ((input[*i] == '"' || input[*i] == '\''))
			*i += ft_wordlen(input + *i) + 2;
		else
			*i += ft_wordlen(input + *i);
	}
	return (true);
}

bool	ft_tokenization(t_minishell *minishell, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_unclosed_quotes(input))
			return (ft_error("Unclosed quotes"), false);
		while (ft_space(input[i]))
			i++;
		if ((!ft_strncmp(input + i, "|", 1) && !ft_token(minishell, input, &i,
					PIPE)) || (!ft_strncmp(input + i, ">", 1)
				&& !ft_token(minishell, input, &i, GREAT)) || (!ft_strncmp(input
					+ i, "<", 1) && !ft_token(minishell, input, &i, LESS))
			|| (!ft_strncmp(input + i, ">>", 2) && !ft_token(minishell, input,
					&i, GREATGREAT)) || (!ft_strncmp(input + i, "<<", 2)
				&& !ft_token(minishell, input, &i, LESSLESS))
			|| (!ft_space(input[i]) && !ft_notword(input[i])
				&& !ft_token(minishell, input, &i, WORD)))
			return (false);
	}
	return (true);
}

bool	ft_token_order(t_minishell *minishell)
{
	t_token	*current_token;

	current_token = minishell->token_list;
	while (current_token)
	{
		if (current_token->token_id == 0)
		{
			if (current_token->token_redir == REDIR && (!current_token->next_token 
					|| current_token->next_token->token_type == PIPE))
			{
				ft_error("Syntax error near unexpected token '|'");
				return (false);
			}
			if (current_token->token_type == PIPE && (current_token->token_id == 0 || !current_token->next_token
					|| current_token->next_token->token_type == PIPE))
			{
				ft_error("Syntax error near unexpected token '|'");
				return (false);
			}
		}
		current_token = current_token->next_token;
	}
	return (true);
}


// void	ft_parsing(t_minishell *minishell, char *input)
// turned int main for testing purposes
int	main(void)
{
	t_minishell	minishell;
	char		*input;
	t_token		*current_token;

	input = "grep -c 'hello world' | wc -l > file.txt";
	minishell.token_list = NULL;
	if (!ft_tokenization(&minishell, input))
		return (1); // error

	// check if token chained list is correct
	printf("Input: %s\n", input);
	current_token = minishell.token_list;
	while (current_token)
	{
		printf("token_id: %d ; ", current_token->token_id);
		printf("token_name: %s ; ", current_token->token_name);
		printf("token_type: %d ; ", current_token->token_type);
		printf("token_redir: %d\n", current_token->token_redir);
		current_token = current_token->next_token;
	}
	printf("Null node: %p\n", current_token);
	
	// if (!ft_token_order(&minishell))
	// 	return (1); // error
	return (0);
}

// not interpreted:
// check unclosed single/double quotes -> DONE
// backslash \ or semicolon ;
// parenthesis () {} [] and & (not in subject)
// wildcards *, &&, || (bonus)

// lexer -> tokenization
// 1. only spaces
// skip
// 2. if word
// add to token list except if quotes not closed
// 3. if redirections
// add to token list
// 4. if pipe
// add to token list
// i++ until end of string

// parser -> bash syntax -> algorithm
// go through token list and check order of tokens
// check if command exist with acces function