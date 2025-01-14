/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:09:26 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/14 19:17:50 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
    t_minishell	minishell;
    char		*input;
	t_token		*current_token;

    (void)ac;
    (void)av;
    ft_bzero(&minishell, sizeof(t_minishell));
    while (1)
    {
		input = readline("minishell$ ");
		if (!input)
		    continue ;
		if (!ft_parsing(&minishell, input))
		{
			ft_free_token_list(&minishell);
			free(input);
		    continue ;
		}
		// following part is for testing purposes
		printf("Input: %s\n", input);
		current_token = minishell.token_list;
		while (current_token)
		{
			printf("Node n* (token_id): %d \n", current_token->token_id);
			printf("token_name: %s ; ", current_token->token_name);
			printf("token_name length: %zu ; ", ft_strlen(current_token->token_name));
			printf("token_type: %d ; ", current_token->token_type);
			printf("token_redir: %d\n", current_token->token_redir);
			current_token = current_token->next_token;
		}
		printf("Null node: %p\n", current_token);
		ft_free_token_list(&minishell);
		minishell.token_list = NULL;
		free(input);
		input = NULL;
    }
    return (0);
}
