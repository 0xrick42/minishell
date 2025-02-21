/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:15:22 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/02/14 12:35:45 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_cmd(t_cmd *cmd)
{
	cmd->cmd_name = NULL;
	cmd->cmd_args = NULL;
	cmd->next_cmd = NULL;
}

static bool	ft_add_cmd(t_minishell *minishell, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!minishell->cmd_list)
	{
		minishell->cmd_list = new_cmd;
		return (true);
	}
	current = minishell->cmd_list;
	while (current->next_cmd)
		current = current->next_cmd;
	current->next_cmd = new_cmd;
	return (true);
}

static bool	ft_create_cmd(t_minishell *minishell, char **cmd_args)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (false);
	ft_init_cmd(new_cmd);
	new_cmd->cmd_name = ft_strdup(cmd_args[0]);
	new_cmd->cmd_args = cmd_args;
	return (ft_add_cmd(minishell, new_cmd));
}

bool	ft_create_cmd_list(t_minishell *minishell, char **cmd_cells)
{
	int	i;

	i = 0;
	while (cmd_cells[i])
	{
		if (!ft_cmd_list(cmd_cells[i], minishell))
		{
			ft_free_cmd_list(minishell->cmd_list);
			minishell->cmd_list = NULL;
			return (false);
		}
		i++;
	}
	return (true);
}
