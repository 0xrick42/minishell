/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
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
