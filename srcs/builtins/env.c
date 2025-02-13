/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_minishell *minishell)
{
	t_envar	*current;

	current = minishell->env_list;
	while (current)
	{
		if (current->value)
		{
			ft_putstr_fd(current->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(current->value, 1);
		}
		current = current->next;
	}
	return (0);
}
