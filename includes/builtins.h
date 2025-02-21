/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:10:45 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/25 20:35:18 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <limits.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* Echo builtin */
int		ft_echo(char **args);

/* CD builtin */
int		ft_cd(t_minishell *minishell, char **args);
char	*ft_get_home_path(t_minishell *minishell);
char	*ft_get_oldpwd(t_minishell *minishell);
int		ft_update_pwd(t_minishell *minishell);

/* PWD builtin */
int		ft_pwd(void);

/* Export builtin */
int		ft_export(t_minishell *minishell, char **args);
int		ft_check_export_syntax(char *arg);
void	ft_sort_env(char **env_array, int size);
char	**ft_env_to_array(t_minishell *minishell);

/* Unset builtin */
int		ft_unset(t_minishell *minishell, char **args);
int		ft_check_unset_syntax(char *arg);

/* Env builtin */
int		ft_env(t_minishell *minishell);

/* Exit builtin */
int		ft_exit(t_minishell *minishell, char **args);
int		ft_is_numeric(char *str);

#endif 