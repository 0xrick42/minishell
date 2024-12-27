/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:52 by aistierl          #+#    #+#             */
/*   Updated: 2024/12/27 20:36:34 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_addtolist_token(t_minishell *minishell, t_token *new_token)
{
    t_token *current_token;
    
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

void    ft_create_token(t_minishell *minishell, char *input, t_token_type type)
{
    t_token *new_token;
    
    new_token = malloc(sizeof(t_token));
    if (!new_token)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_token->token_name = input;
    new_token->token_type = type;
    new_token->next_token = NULL;
    ft_addtolist_token(minishell, new_token);
}


void    ft_tokenization(t_minishell *minishell, char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n') 
            i++;
        if (input[i] == '\0')
            break;
        else if (ft_strncmp(input + i, "|", 1) == 0)
        {
            // create new pipe token
            // add pipe token to list
            i++;
        }
        else if (ft_strncmp(input + i, ">", 1) == 0 || ft_strncmp(input + i, "<", 1) == 0)
        {
            // create new redirection token
            // add redirection token to list
            i++;
        }
        else if (ft_strncmp(input + i, ">>", 2) == 0 || ft_strncmp(input + i, "<<", 2) == 0)
        {
            // create new redirection token
            // add redirection token to list
            i++;
        }
        else //////////////////
        {
            // create new word token;
            // add word token to list
            i++;
        }
    }
}

void    ft_parsing(t_minishell *minishell, char *input)
{   
    // not interpreted:
    // check unclosed single/double quotes

    // backslash \ or semicolon ;
    // parenthesis () {} [] and & (not in subject)
    // wildcards *, &&, || (bonus)
    
    
    // lexer -> tokenization
    // 1. only spaces
    // 2. if word
        // add to token list
    // 3. if redirection
        // add to token list
    // 4. if pipe
        // add to token list
    // i++ until end of string
    
    // parser -> check syntax 
    // go through token list and check order of tokens
    //  check if command exist etc
}