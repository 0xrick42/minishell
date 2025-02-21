/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:15:22 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/30 12:45:38 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*ft_expand(t_minishell *minishell, char *str)
{
	char	*expanded;
	char	*result;

	if (!str)
		return (NULL);
	expanded = ft_process_string(minishell, str);
	if (!expanded)
		return (NULL);
	if (ft_is_quoted(expanded))
	{
		result = ft_remove_quotes(expanded);
		free(expanded);
		return (result);
	}
	return (expanded);
}
