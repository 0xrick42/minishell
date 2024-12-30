/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:52 by aistierl          #+#    #+#             */
/*   Updated: 2024/12/30 19:33:47 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_append_token(t_minishell *minishell, t_token *new_token)
{
	t_token	*current_token;

	if (minishell->token_list == NULL)
		minishell->token_list = new_token;
	else
	{
		current_token = minishell->token_list;
		while (current_token->next_token != NULL)
			current_token = current_token->next_token;
		current_token->next_token = new_token;
	}
	return ;
}

bool	ft_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	return (false);
}

bool	ft_notword(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
}

void	ft_error(char *error_message)
{
	printf("Error: %s.\n", error_message);
	return ;
}

int	ft_wordlen(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i] && !ft_space(input[i]) && !ft_notword(input[i]))
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\"' && input[i] != '\'')
			{
				i++;
				count++;
			}
			if (!input[i])
				return (-1);
			break ;
		}
		i++;
		count++;
	}
	return (count);
}

bool	ft_create_word_token(t_token *word_token, char *input)
{
	if (input[0] == '"' || input[0] == '\'')
	{
		if (ft_wordlen(input) == -1)
		{	
			ft_error("Unclosed quotes");
			return (false);
		}
		word_token->token_name = ft_substr(input, 1, ft_wordlen(input));
	}
	else
		word_token->token_name = ft_substr(input, 0, ft_wordlen(input));
	return (true);
}

bool	ft_create_all_token(t_minishell *minishell, char *input, t_token_type type)
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
		if (ft_create_word_token(new_token, input) == false)
			return (free(new_token), false);
	}
	if (!new_token->token_name)
		return (free(new_token), false);
	new_token->token_type = type;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
	return (true);
}

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

bool	ft_tokenization(t_minishell *minishell, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (ft_space(input[i]))
			i++;
		if (ft_strncmp(input + i, "|", 1) == 0)
		{
			if (!ft_create_all_token(minishell, input + i, PIPE))
				return (ft_free_token_list(minishell), false);
			i++;
		}
		else if (ft_strncmp(input + i, ">", 1) == 0)
		{
			if (!ft_create_all_token(minishell, input + i, GREAT))
				return (ft_free_token_list(minishell), false);
			i++;
		}
		else if (ft_strncmp(input + i, "<", 1) == 0)
		{
			if (!ft_create_all_token(minishell, input + i, LESS))
				return (ft_free_token_list(minishell), false);
			i++;
		}
		else if (ft_strncmp(input + i, ">>", 2) == 0)
		{
			if (!ft_create_all_token(minishell, input + i, GREATGREAT))
				return (ft_free_token_list(minishell), false);
			i += 2;
		}
		else if (ft_strncmp(input + i, "<<", 2) == 0)
		{
			if (!ft_create_all_token(minishell, input + i, LESSLESS))
				return (ft_free_token_list(minishell), false);
			i += 2;
		}
		else if (!ft_space(input[i]) && !ft_notword(input[i]))
		{
			if (!ft_create_all_token(minishell, input + i, WORD))
				return (ft_free_token_list(minishell), false);
			if (input[i] == '"' || input[i] == '\'')
				i += ft_wordlen(input + i) + 2;
			else
				i += ft_wordlen(input + i);
		}
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

	input = "ls -l | grep -c 'hello' > file.txt";
	minishell.token_list = NULL;
	if (!ft_tokenization(&minishell, input))
		return (1); // error
	
	// check if token chained list is correct
	printf("Input: %s\n", input);
	current_token = minishell.token_list;
	while (current_token)
	{
		printf("token_name: %s ", current_token->token_name);
		printf("token_type: %d\n", current_token->token_type);
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