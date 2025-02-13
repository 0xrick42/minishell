/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:48:20 by aistierl          #+#    #+#             */
/*   Updated: 2025/02/13 16:48:45 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_table(char **table)
{
	int		i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	free(table);
	table = NULL;
}

void	ft_free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current_cmd;
	t_cmd	*tmp;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		tmp = current_cmd->next_cmd;
		free(current_cmd->cmd_name);
		ft_free_table(current_cmd->cmd_args);
		free(current_cmd);
		current_cmd = tmp;
	}
	cmd_list = NULL;
	return ;
}

char	**ft_split_cmd_args(char *cmd_cell)
{
	char	**cmd_args;
	int		i;
	bool		quote_flag;
	
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
		cmd_args = ft_split_quotes(cmd_cell, ' ');		
	return (cmd_args);
}

bool	ft_cmd_list(char *cmd_cell, t_minishell *minishell)
{
	t_cmd	*new_cmd;
	t_cmd	*current_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (ft_free_cmd_list(minishell->cmd_list), false);
	new_cmd->cmd_name = ft_strdup(cmd_cell);
	if (!new_cmd->cmd_name)
		return (ft_free_cmd_list(minishell->cmd_list), false);
	new_cmd->cmd_args = ft_split_cmd_args(cmd_cell);
	if (!new_cmd->cmd_args)
		return (ft_free_cmd_list(minishell->cmd_list), false);
	new_cmd->next_cmd = NULL;
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
	(void)minishell;

	cmd_table = ft_split_quotes(input, '|');
	if (!cmd_table)
		return (false);
	i = 0;
	// while (cmd_table[i])
	// {
	// 	printf("test %s\n", cmd_table[i]);
	// 	i++;
	// }
	i = 0;
	while (cmd_table[i])
	{
		if (!ft_cmd_list(cmd_table[i], minishell))
			return (ft_free_table(cmd_table), false);
		i++;
	}
	ft_free_table(cmd_table);
    return (true);
}