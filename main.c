/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:09:26 by aistierl          #+#    #+#             */
/*   Updated: 2025/02/27 19:09:55 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_test_token(t_minishell *minishell, char *input)
{
	t_token			*current_token;
	
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
}

void	ft_test_env(t_minishell *minishell, char **envp)
{
	t_envar			*current_envar;
	int				i;
	
	current_envar = minishell->env_list;
	i = 0;
	while (current_envar)
	{
		printf("envar: %s\n", envp[i]);
		printf("key: %s\n", current_envar->key);
		printf("value: %s\n", current_envar->value);
		current_envar = current_envar->next;
		i++;
	}
}

void	ft_test_cmd(t_minishell *minishell)
{
	t_cmd			*current_cmd;
	t_redir			*current_redir;
	int				i;
	
	current_cmd = minishell->cmd_list;
	current_redir = minishell->cmd_list->redir_list;
	while (current_cmd)
	{
		i = 0;
		printf("cmd_pos: %d\n", current_cmd->cmd_pos);
		printf("whole_cmd: %s\n", current_cmd->whole_cmd);
		printf("cmd_name: %s\n", current_cmd->cmd_name);
		printf("cmd_args: ");
		while (current_cmd->cmd_args[i])
		{
			printf("[%s] ", current_cmd->cmd_args[i]);
			i++;
		}
		printf("\n");			
		current_redir = current_cmd->redir_list;
		while (current_redir)
		{
			printf("redir_type: %s ", current_redir->redir_type);
			printf("redir_file: %s\n", current_redir->redir_file);
			current_redir = current_redir->next_redir;
		}
		printf("previous cmd: %p\n", current_cmd->prev_cmd);
		printf("\n");
		current_cmd = current_cmd->next_cmd;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell		*minishell;
	char			*input;

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
	minishell->token_list = NULL;
	minishell->env_list = NULL;
	minishell->cmd_list = NULL;
	if (!ft_envar_list(envp, minishell))
		return (1);
	while (1)
	{
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
		// ft_test_token(minishell, input);	
		// ft_test_env(minishell, envp);
		// end of testing part
		if (!ft_cmd_struct(input, minishell))
			return (1);
		// following part is for testing purposes
		ft_test_cmd(minishell);
		// end of testing part	
		ft_free_token_list(minishell);
		ft_free_cmd_list(minishell);
		free(input);
		input = NULL;
	}
	rl_clear_history();
	return (0);
}



// pbm pour liste de redir quand plusieurs redir dans une cmd a corriger
// pbm free liste de redir
// verifier si liste chainee envar bien convertie en tableau (while + printf envar[i])