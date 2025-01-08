/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:48 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/08 18:19:19 by aistierl         ###   ########.fr       */
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

typedef enum e_token_redir
{
	NONE,
	REDIR,
}					t_token_redir;

typedef enum e_token_type
{
	WORD,
	GREAT, // output redirection
	GREATGREAT, // append output redirection
	LESS, // input redirection
	LESSLESS, // here doc
	PIPE,
}					t_token_type;

typedef struct s_token
{
	int				token_id;
	char			*token_name;
	t_token_type	token_type;
	t_token_redir	token_redir;
	struct s_token	*next_token;
}					t_token;

typedef struct s_minishell
{
	t_token			*token_list;
}					t_minishell;

void				ft_append_token(t_minishell *minishell, t_token *new_token);
void				ft_free_token_list(t_minishell *minishell);
int					ft_token_redir(t_token_type type);

int					ft_wordlen(char *input);
bool				ft_space(char c);
bool				ft_notword(char c);
bool				ft_unclosed_quotes(char *input);

#endif