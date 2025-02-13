/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*ft_get_env_value(t_minishell *minishell, char *var_name)
{
	t_envar	*current;

	current = minishell->env_list;
	while (current)
	{
		if (ft_strncmp(current->key, var_name, ft_strlen(var_name) + 1) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*ft_expand_var(t_minishell *minishell, char *var_name)
{
	char	*value;

	if (!var_name || !*var_name)
		return (ft_strdup("$"));
	value = ft_get_env_value(minishell, var_name);
	if (!value)
		return (NULL);
	return (value);
}

char	*ft_expand_dollars(t_minishell *minishell, char *str, int *i)
{
	char	*var_name;
	char	*expanded;

	(*i)++;
	if (!str[*i] || str[*i] == ' ' || str[*i] == '$')
		return (ft_strdup("$"));
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(0));
	}
	var_name = ft_get_var_name(str, i);
	if (!var_name)
		return (NULL);
	expanded = ft_expand_var(minishell, var_name);
	free(var_name);
	return (expanded);
}
