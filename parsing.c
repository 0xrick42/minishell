/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:52 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/10 16:24:05 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *error_message)
{
	printf("Minishell: %s\n", error_message);
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
		else if (!ft_strncmp(input + i, ">>", 2) && !ft_ggreat(minishell, &i))
			return (false);
		else if (!ft_strncmp(input + i, "<<", 2) && !ft_lless(minishell, &i))
			return (false);
		else if (!ft_strncmp(input + i, ">", 1) && !ft_great(minishell, &i))
			return (false);
		else if (!ft_strncmp(input + i, "<", 1) && !ft_less(minishell, &i))
			return (false);
		else if (!ft_space(input[i]) && !ft_notword(input[i])
			&& !ft_word(minishell, input, &i))
			return (false);
	}
	return (true);
}


bool	ft_token_order(t_minishell *minishell)
{
	if (!ft_check_pipe(minishell))
		return (false);
	if (!ft_check_redir(minishell))
		return (false);
	return (true);
}


// void	ft_parsing(t_minishell *minishell, char *input)
// turned int main for testing purposes
int	main(void)
{
	t_minishell	minishell;
	char		*input;
	t_token		*current_token;

	input = "<<< ls -l | grep \"minishell.h\" | wc -l > /doc/\"file txt\"";

	minishell.token_list = NULL;
	if (!ft_not_handling(input))
		return (1); // error
	if (!ft_unclosed_quotes(input))
		return (1); // error
	if (!ft_tokenization(&minishell, input, 0))
		return (1); // error
	if (!ft_token_order(&minishell))
		return (1); // error

	// check if token chained list is correct
	printf("Input: %s\n", input);
	current_token = minishell.token_list;
	while (current_token)
	{
		printf("token_id: %d ; ", current_token->token_id);
		printf("token_name: %s ; ", current_token->token_name);
		printf("token_name length: %zu ; ", ft_strlen(current_token->token_name));
		printf("token_type: %d ; ", current_token->token_type);
		printf("token_redir: %d\n", current_token->token_redir);
		current_token = current_token->next_token;
	}
	printf("Null node: %p\n", current_token);
	

	return (0);
}

// not interpreted:
// check unclosed single/double quotes -> DONE
// backslash \ or semicolon ;
// parenthesis () {} [] and & (not in subject)
// wildcards *, &&, || (bonus)

