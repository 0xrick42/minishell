/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:33:48 by aistierl          #+#    #+#             */
/*   Updated: 2025/02/27 17:37:16 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_lst_size(t_envar *env_list)
{
	t_envar		*current;
	int			i;

	i = 0;
	current = env_list;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	**ft_envar_tab(t_minishell *minishell)
{
	t_envar		*current;
	char		**envar_tab;
	char		*temp;
	int			i;
	
	envar_tab = malloc(sizeof(char *) * (ft_lst_size(minishell->env_list) + 1));
	if (!envar_tab)
		return (NULL);
	i = 0;
	current = minishell->env_list;
	while (current)
	{
		temp = ft_strjoin(current->key, "=");
		if (!temp)
			return (NULL);
		envar_tab[i] = ft_strjoin(temp, current->value);
		if (!envar_tab[i])
			return (NULL);
		free(temp);
		current = current->next;
		i++;
	}
	envar_tab[i] = NULL;
	return (envar_tab);
}


char	*ft_get_key(char *envp, char c)
{
	char	*key;
	int		i;

	i = 0;
	while (envp[i] && envp[i] != c)
		i++;
	key = ft_substr(envp, 0, i);
	if (!key)
		return (NULL);
	return (key);
}

char	*ft_get_value(char *envar, int start)
{
	char	*value;

	value = ft_strdup(envar + start);
	if (!value)
		return (NULL);
	return (value);
}

bool	ft_add_envar(t_minishell *minishell, char *key, char *value)
{
	t_envar		*new_envar;
	t_envar		*current;

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

	if (!envp)
		return (false);
	i = 0;
	while (envp[i])
	{
		key = ft_get_key(envp[i], '=');
		if (!key)
			return (false);
		value = ft_get_value(envp[i], ft_strlen(key) + 1);
		if (!value)
			return (free(key), false);
		if (!ft_add_envar(minishell, key, value))
			return (false);
		i++;
	}
	return (true);
}
