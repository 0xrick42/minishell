/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:10:33 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/02/14 21:45:18 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_exit_status(t_minishell *minishell, int status)
{
	minishell->exit_status = status;
}

int	ft_get_exit_status(t_minishell *minishell)
{
	return (minishell->exit_status);
}
