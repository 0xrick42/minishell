/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:52 by aistierl          #+#    #+#             */
/*   Updated: 2024/12/29 20:18:25 by aistierl         ###   ########.fr       */
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

int	ft_wordlen(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i] && !ft_space(input[i]) && !ft_notword(input[i]))
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '"' && input[i] != '\'')
			{
            	i++;
			    count++;
            }
            break ;
		}
		i++;
		count++;
	}
	return (count);
}

void	ft_create_token(t_minishell *minishell, char *input, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	if (type == PIPE || type == GREAT || type == LESS)
		new_token->token_name = ft_substr(input, 0, 1);
	else if (type == GREATGREAT || type == LESSLESS)
		new_token->token_name = ft_substr(input, 0, 2);
	else if (type == WORD)
    {
        if (input[0] == '"' || input[0] == '\'')
            new_token->token_name = ft_substr(input, 1, ft_wordlen(input));
        else
    	    new_token->token_name = ft_substr(input, 0, ft_wordlen(input));
    }
    if (!new_token->token_name)
	{
		free(new_token);
		return ; // error handling, need to exit function and free the whole token list
	}
	new_token->token_type = type;
	new_token->next_token = NULL;
	ft_append_token(minishell, new_token);
}

// void	ft_tokenization(t_minishell *minishell, char *input)
// turned into main for testing purposes
int    main(void)
{
	int	i;
    t_minishell minishell;
    char *input = "ls -l | grep .c > file.c";

    minishell.token_list = NULL;
	i = 0;
	while (input[i])
	{
		while (ft_space(input[i]))
			i++;
		if (ft_strncmp(input + i, "|", 1) == 0)
		{
			ft_create_token(&minishell, input + i, PIPE);
			i++;
		}
		else if (ft_strncmp(input + i, ">", 1) == 0)
		{
			ft_create_token(&minishell, input + i, GREAT);
			i++;
		}
		else if (ft_strncmp(input + i, "<", 1) == 0)
		{
			ft_create_token(&minishell, input + i, LESS);
			i++;
		}
		else if (ft_strncmp(input + i, ">>", 2) == 0)
		{
			ft_create_token(&minishell, input + i, GREATGREAT);
			i += 2;
		}
		else if (ft_strncmp(input + i, "<<", 2) == 0)
		{
			ft_create_token(&minishell, input + i, LESSLESS);
			i += 2;
		}
		else if (!ft_space(input[i]) && !ft_notword(input[i]))
		{
			ft_create_token(&minishell, input + i, WORD);
			i += ft_wordlen(input + i);
		}
	}
    // check if token chained list is correct
    t_token *current_token = minishell.token_list;
    printf("Input: %s\n", input);
    while (current_token)
    {
        printf("token_name: %s ", current_token->token_name);
        printf("token_type: %d\n", current_token->token_type);
        current_token = current_token->next_token;
    }
    printf("Null node: %p\n", current_token);
    return (0);
}

// void	ft_parsing(t_minishell *minishell, char *input)
// {
// 	// not interpreted:
// 	// check unclosed single/double quotes

// 	// backslash \ or semicolon ;
// 	// parenthesis () {} [] and & (not in subject)
// 	// wildcards *, &&, || (bonus)

// 	// lexer -> tokenization
// 	// 1. only spaces
// 	// 2. if word
// 	// add to token list
// 	// 3. if redirection
// 	// add to token list
// 	// 4. if pipe
// 	// add to token list
// 	// i++ until end of string

// 	// parser -> check syntax
// 	// go through token list and check order of tokens
// 	//  check if command exist etc
// }