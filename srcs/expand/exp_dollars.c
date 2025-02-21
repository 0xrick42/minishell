/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:25:33 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/30 19:40:15 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*ft_get_env_value(t_minishell *minishell, char *var_name)
{
	t_envar	*current;

	if (!var_name || !*var_name)
		return (ft_strdup("$"));
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(ft_get_last_status(minishell)));
	current = minishell->env_list;
	while (current)
	{
		if (ft_strcmp(current->key, var_name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup(""));
}

static char	*ft_handle_special_var(t_minishell *minishell, char c, int *i)
{
	(*i)++;
	if (c == '?')
		return (ft_itoa(ft_get_last_status(minishell)));
	if (c == '$')
		return (ft_itoa(getpid()));
	return (ft_strdup("$"));
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
	if (str[*i] == '?' || str[*i] == '$')
		return (ft_handle_special_var(minishell, str[*i], i));
	if (str[*i] == '\'' && !ft_in_quotes(str, *i - 1))
		return (ft_strdup("$"));
	var_name = ft_get_var_name(str, i);
	if (!var_name)
		return (NULL);
	expanded = ft_expand_var(minishell, var_name);
	free(var_name);
	return (expanded);
}
