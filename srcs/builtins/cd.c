/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:20:33 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/02/01 16:45:18 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <limits.h>

char	*ft_get_home_path(t_minishell *minishell)
{
	t_envar	*current;

	current = minishell->env_list;
	while (current)
	{
		if (ft_strncmp(current->key, "HOME", 5) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	ft_update_pwd(t_minishell *minishell)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;
	t_envar	*current;

	if (!getcwd(cwd, PATH_MAX))
		return (0);
	current = minishell->env_list;
	while (current)
	{
		if (ft_strncmp(current->key, "PWD", 4) == 0)
		{
			old_pwd = current->value;
			current->value = ft_strdup(cwd);
			if (!current->value)
				return (0);
			free(old_pwd);
			return (1);
		}
		current = current->next;
	}
	return (1);
}

int	ft_cd(t_minishell *minishell, char **args)
{
	char	*path;

	if (!args[1])
	{
		path = ft_get_home_path(minishell);
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	if (!ft_update_pwd(minishell))
		return (1);
	return (0);
}
