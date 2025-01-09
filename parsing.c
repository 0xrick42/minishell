/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:52 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/09 13:15:55 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *error_message)
{
	printf("Error: %s.\n", error_message);
	return ;
}

bool	ft_tokenization(t_minishell *minishell, char *input, int i)
{	
	while (input[i])
	{
		while (ft_space(input[i]))
			i++;
		if (!ft_strncmp(input + i, "|", 1) && !ft_pipe(minishell, &i))
			return (false);
		else if (!ft_strncmp(input + i, ">", 1) && !ft_great(minishell, &i))
			return (false);
		else if (!ft_strncmp(input + i, "<", 1) && !ft_less(minishell, &i))
			return (false);
		else if (!ft_strncmp(input + i, ">>", 2) && !ft_ggreat(minishell, &i))
			return (false);
		else if (!ft_strncmp(input + i, "<<", 2) && !ft_lless(minishell, &i))
			return (false);
		else if (!ft_space(input[i]) && !ft_notword(input[i])
			&& !ft_word(minishell, input, &i))
			return (false);
	}
	return (true);
}

// bool	ft_token_order(t_minishell *minishell)
// {
// 	t_token	*current_token;

// 	current_token = minishell->token_list;
// 	while (current_token)
// 	{
// 		if (current_token->token_id == 0)
// 		{
// 			if (current_token->token_redir == REDIR && (!current_token->next_token 
// 					|| current_token->next_token->token_type == PIPE))
// 			{
// 				ft_error("Syntax error near unexpected token '|'");
// 				return (false);
// 			}
// 			if (current_token->token_type == PIPE && (current_token->token_id == 0 || !current_token->next_token
// 					|| current_token->next_token->token_type == PIPE))
// 			{
// 				ft_error("Syntax error near unexpected token '|'");
// 				return (false);
// 			}
// 		}
// 		current_token = current_token->next_token;
// 	}
// 	return (true);
// }


// void	ft_parsing(t_minishell *minishell, char *input)
// turned int main for testing purposes
int	main(void)
{
	t_minishell	minishell;
	char		*input;
	t_token		*current_token;

	input = "grep -c 'hello world' | wc -l > file.txt";

	minishell.token_list = NULL;
	if (!ft_unclosed_quotes(input))
		return (ft_error("Unclosed quotes"), false);
	if (!ft_tokenization(&minishell, input, 0))
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

