/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

/* Main expansion functions */
char	*ft_expand(t_minishell *minishell, char *str);
char	*ft_process_string(t_minishell *minishell, char *str);
char	*ft_expand_dollars(t_minishell *minishell, char *str, int *i);
char	*ft_expand_var(t_minishell *minishell, char *var_name);

/* Expansion utilities */
int		ft_is_var_char(char c);
char	*ft_get_var_name(char *str, int *i);
char	*ft_join_expanded(char *str1, char *str2);
void	ft_skip_quotes(char *str, int *i, char quote);
int		ft_count_dollars(char *str);

/* Quote handling */
int		ft_in_quotes(char *str, int pos);
int		ft_is_quoted(char *str);
char	*ft_remove_quotes(char *str);

#endif 