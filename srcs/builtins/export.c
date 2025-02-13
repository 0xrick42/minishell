/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	ft_is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	ft_update_env_var(t_minishell *minishell, char *key, char *value)
{
	t_envar	*current;

	current = minishell->env_list;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			free(current->value);
			current->value = value;
			return ;
		}
		current = current->next;
	}
	ft_add_envar(minishell, key, value);
}

static int	ft_handle_export_arg(t_minishell *minishell, char *arg)
{
	char	*key;
	char	*value;
	char	*equals;

	if (!ft_is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	equals = ft_strchr(arg, '=');
	if (!equals)
		return (0);
	key = ft_substr(arg, 0, equals - arg);
	if (!key)
		return (1);
	value = ft_strdup(equals + 1);
	if (!value)
	{
		free(key);
		return (1);
	}
	ft_update_env_var(minishell, key, value);
	return (0);
}

static void	ft_print_export_list(t_minishell *minishell)
{
	t_envar	*current;

	current = minishell->env_list;
	while (current)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(current->key, 1);
		if (current->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		current = current->next;
	}
}

int	ft_export(t_minishell *minishell, char **args)
{
	int	i;
	int	status;

	status = 0;
	if (!args[1])
	{
		ft_print_export_list(minishell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (ft_handle_export_arg(minishell, args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
