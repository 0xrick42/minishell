/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:09:26 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/22 18:39:54 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_get_key(char *envp, char c)
{
	char	*key;
	int	i;

	i = 0;
	while (envp[i] && envp[i] != c)
		i++;
	key = ft_substr(envp, 0, i);
	if (!key)
		return (NULL);
	return (key);
}

char *ft_get_value(char *envar, int start)
{
	char	*value;

	value = ft_strdup(envar + start);
	if (!value)
		return (NULL);
	return (value);
}

bool	ft_add_envar(t_envar *env_list, char *key, char *value)
{
	t_envar	*new_envar;
	t_envar	*current;

	new_envar = malloc(sizeof(t_envar));
	if (!new_envar)
		return (false);
	new_envar->key = key;
	new_envar->value = value;
	new_envar->next = NULL;
	if (!env_list)
	{
		env_list = new_envar;
		return (true);
	}
	current = env_list;
	while (current->next)
		current = current->next;
	current->next = new_envar;
	return (true);
}


bool	ft_envar_list(char **envp, t_minishell *minishell)
{
	int	i;
	char	*key;
	char	*value;

	if (!envp) // bcs env -i
		return (false); // maybe not return false, but create env_list with PWD and SHLVL
	i = 0;
	while (envp[i])
	{
		key = ft_get_key(envp[i], '=');
		if (!key)
			return (false);
		value = ft_get_value(envp[i], ft_strlen(key) + 1);
		if (!value)
			return (free(key), false);
		if (!ft_add_envar(minishell->env_list, key, value))
			return (false);
		i++;
	}
	return (true);
}


int	main(int ac, char **av, char **envp)
{
    t_minishell	*minishell;
    char		*input;
	t_token		*current_token;

    (void)ac;
    (void)av;

	if (!isatty(STDIN_FILENO))
	{
		printf("Minishell requires a terminal. Do better.\n");
		return (1);
	}
	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (1);
    while (1)
    {    
		ft_bzero(minishell, sizeof(t_minishell));	
		if (!ft_envar_list(envp, minishell))
			return (1);
		input = readline("minishell$ ");
		if (!input)
		    continue ;
		add_history(input);
		if (!ft_parsing(minishell, input))
		{
			ft_free_token_list(minishell);
			free(input);
			input = NULL;
		    continue ;
		}
		// following part is for testing purposes
		printf("Input: %s\n", input);
		current_token = minishell->token_list;
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
		ft_free_token_list(minishell);
		free(input);
		input = NULL;
    }
	rl_clear_history();
    return (0);
}
