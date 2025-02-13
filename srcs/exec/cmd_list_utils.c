/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_create_cmd(t_minishell *minishell, char **cmd_args)
{
	t_cmd	*new_cmd;
	t_cmd	*current;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (false);
	new_cmd->cmd_name = ft_strdup(cmd_args[0]);
	if (!new_cmd->cmd_name)
	{
		free(new_cmd);
		return (false);
	}
	new_cmd->cmd_args = cmd_args;
	new_cmd->next_cmd = NULL;
	if (!minishell->cmd_list)
		minishell->cmd_list = new_cmd;
	else
	{
		current = minishell->cmd_list;
		while (current->next_cmd)
			current = current->next_cmd;
		current->next_cmd = new_cmd;
	}
	return (true);
}

void	ft_free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd_list;
	while (current)
	{
		next = current->next_cmd;
		free(current->cmd_name);
		ft_free_table(current->cmd_args);
		free(current);
		current = next;
	}
}

void	ft_free_table(char **table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

bool	ft_cmd_list(char *cmd_cell, t_minishell *minishell)
{
	char	**cmd_args;

	cmd_args = ft_split_cmd_args(cmd_cell);
	if (!cmd_args)
		return (false);
	return (ft_create_cmd(minishell, cmd_args));
}
