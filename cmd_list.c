/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:48:20 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/23 19:19:53 by aistierl         ###   ########.fr       */
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

bool	ft_cmd_list(char **cmd_table, t_minishell *minishell)
{
    int		i;

    i = 0;
    while (cmd_table[i])
    {
        if (!ft_cmd_args(cmd_table[i], minishell))
            return (false);
        i++;
    }
    return (true);
}



bool	ft_cmd_struct(char *input, t_minishell *minishell)
{
	char	**cmd_table;

	cmd_table = ft_split(input, '|');
	if (!cmd_table)
		return (false);
	if (!ft_cmd_list(cmd_table, minishell))
	{
		ft_free_table(cmd_table);
		return (false);
	}
	ft_free_table(cmd_table);
    return (true);
}