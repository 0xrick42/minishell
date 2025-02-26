/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:48:20 by aistierl          #+#    #+#             */
/*   Updated: 2025/02/26 19:03:16 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_table(char **table)
{
	int		i;

	i = 0;
	while (table && table[i])
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	free(table);
	table = NULL;
}

void	ft_free_cmd_list(t_minishell *minishell)
{
	t_cmd	*current_cmd;
	t_cmd	*tmp;

	current_cmd = minishell->cmd_list;
	while (current_cmd)
	{
		tmp = current_cmd->next_cmd;
		free(current_cmd->cmd_name);
		current_cmd->cmd_name = NULL;
		free(current_cmd->whole_cmd);
		current_cmd->whole_cmd = NULL;
		ft_free_table(current_cmd->cmd_args);
		free(current_cmd);
		current_cmd = tmp;
	}
	minishell->cmd_list = NULL;
	return ;
}

char	**ft_split_cmd_args(char *cmd_cell)
{
	char	**cmd_args;
	int		i;
	bool	quote_flag;

	i = 0;
	quote_flag = false;
	while (cmd_cell && cmd_cell[i])
	{
		if (cmd_cell[i] == '"' || cmd_cell[i] == '\'')
		{	
			quote_flag = true;
			break ;
		}
		i++;
	}
	if (quote_flag == false)
		cmd_args = ft_split(cmd_cell, ' ');
	else
		cmd_args = ft_split_quotes(cmd_cell);
	return (cmd_args);
}

bool	ft_redir_list_init(t_cmd *cmd)
{
	t_redir	*new_redir;
	t_redir	*current_redir;
	int		i;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (false);
	i = 0;
	while (cmd->cmd_args)
	{
		if (ft_strcmp(cmd->cmd_args[i], ">") == 0)
		{
			new_redir->redir_type = ">";
			new_redir->redir_file = ft_strdup(cmd->cmd_args[i + 1]);
			if (!new_redir->redir_file)
				return (false);
		}
		else if (ft_strcmp(cmd->cmd_args[i], ">>") == 0)
		{
			new_redir->redir_type = ">>";
			new_redir->redir_file = ft_strdup(cmd->cmd_args[i + 1]);
			if (!new_redir->redir_file)
				return (false);
		}
		else if (ft_strcmp(cmd->cmd_args[i], "<") == 0)
		{
			new_redir->redir_type = "<";
			new_redir->redir_file = ft_strdup(cmd->cmd_args[i + 1]);
			if (!new_redir->redir_file)
				return (false);
		}
		else if (ft_strcmp(cmd->cmd_args[i], "<<") == 0)
		{
			new_redir->redir_type = "<<";
			new_redir->redir_file = NULL;
		}
		else
			break ;
	}
	while (cmd->redir_list)
		cmd->redir_list = new_redir;
	current_redir = new_redir;
	
	
	new_redir->redir_type = NULL;
	
	new_redir->redir_file = NULL;
	new_redir->next_redir = NULL;

}

bool	ft_cmd_init(t_cmd *new_cmd, t_minishell *minishell, char *cmd_cell)
{
	new_cmd->whole_cmd = ft_strdup(cmd_cell);
	if (!new_cmd->whole_cmd)
		return (ft_free_cmd_list(minishell), false);
	new_cmd->cmd_args = ft_split_cmd_args(cmd_cell);
	if (!new_cmd->cmd_args)
		return (ft_free_cmd_list(minishell), false);
	new_cmd->cmd_name = ft_strdup(new_cmd->cmd_args[0]);
	if (!new_cmd->cmd_name)
		return (ft_free_cmd_list(minishell), false);
	if (!ft_redir_list_init(new_cmd))
		return (ft_free_cmd_list(minishell), false);
	new_cmd->next_cmd = NULL;
	return (true);
}

bool	ft_cmd_list(char *cmd_cell, t_minishell *minishell)
{
	t_cmd	*new_cmd;
	t_cmd	*current_cmd;

	current_cmd = NULL;
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (ft_free_cmd_list(minishell), false);
	if (!ft_cmd_init(new_cmd, minishell, cmd_cell))
		return (false);
	if (!minishell->cmd_list)
		minishell->cmd_list = new_cmd;
	else
	{
		current_cmd = minishell->cmd_list;
		while (current_cmd->next_cmd)
			current_cmd = current_cmd->next_cmd;
		current_cmd->next_cmd = new_cmd;
	}
	return (true);
}

bool	ft_cmd_struct(char *input, t_minishell *minishell)
{
	char	**cmd_table;
	int		i;
	
	cmd_table = ft_split_pipes(input);
	if (!cmd_table)
		return (false);
	i = 0;
	while (cmd_table && cmd_table[i])
	{
		if (!ft_cmd_list(cmd_table[i], minishell))
			return (false);
		i++;
	}
	return (true);
}
