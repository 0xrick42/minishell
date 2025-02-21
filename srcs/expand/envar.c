/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:20:15 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/30 16:35:42 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_key(char *envp, char c)
{
	int		i;
	char	*key;

	i = 0;
	while (envp[i] && envp[i] != c)
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (envp[i] && envp[i] != c)
	{
		key[i] = envp[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*ft_get_value(char *envar, int start)
{
	int		i;
	int		j;
	char	*value;

	i = start;
	j = 0;
	while (envar[i])
	{
		i++;
		j++;
	}
	value = malloc(sizeof(char) * (j + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (envar[start])
	{
		value[i] = envar[start];
		i++;
		start++;
	}
	value[i] = '\0';
	return (value);
}

bool	ft_add_envar(t_minishell *minishell, char *key, char *value)
{
	t_envar	*new_envar;
	t_envar	*current;

	new_envar = malloc(sizeof(t_envar));
	if (!new_envar)
		return (false);
	new_envar->key = key;
	new_envar->value = value;
	new_envar->next = NULL;
	if (!minishell->env_list)
	{
		minishell->env_list = new_envar;
		return (true);
	}
	current = minishell->env_list;
	while (current->next)
		current = current->next;
	current->next = new_envar;
	return (true);
}

bool	ft_envar_list(char **envp, t_minishell *minishell)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		key = ft_get_key(envp[i], '=');
		if (!key)
			return (false);
		value = ft_get_value(envp[i], ft_strlen(key) + 1);
		if (!value)
		{
			free(key);
			return (false);
		}
		if (!ft_add_envar(minishell, key, value))
		{
			free(key);
			free(value);
			return (false);
		}
		i++;
	}
	return (true);
}
