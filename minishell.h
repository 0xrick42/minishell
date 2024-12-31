/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:48 by aistierl          #+#    #+#             */
/*   Updated: 2024/12/31 19:38:01 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_token_type
{
	WORD,
	GREAT,
	GREATGREAT,
	LESS,
	LESSLESS,
	PIPE,
}					t_token_type;

typedef struct s_token
{
	char			*token_name;
	t_token_type	token_type;
	struct s_token	*next_token;
}					t_token;

typedef struct s_minishell
{
	t_token			*token_list;
}					t_minishell;

void				ft_append_token(t_minishell *minishell, t_token *new_token);
void				ft_free_token_list(t_minishell *minishell);

int					ft_wordlen(char *input);
bool				ft_space(char c);
bool				ft_notword(char c);

#endif