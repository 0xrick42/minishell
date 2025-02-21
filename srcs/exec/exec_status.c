/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:23:45 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/02/15 16:48:12 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_exit_status(t_minishell *minishell, int status)
{
	if (WIFEXITED(status))
		minishell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->exit_status = 128 + WTERMSIG(status);
	else
		minishell->exit_status = status;
}

int	ft_get_last_status(t_minishell *minishell)
{
	return (minishell->exit_status);
}
