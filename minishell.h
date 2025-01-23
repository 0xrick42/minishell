/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:48 by aistierl          #+#    #+#             */
/*   Updated: 2025/01/23 19:19:51 by aistierl         ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_token_redir
{
	NONE,
	REDIR,
}					t_token_redir;

typedef enum e_token_type
{
	WORD,
	GREAT, // output redirection
	GGREAT, // append output redirection
	LESS, // input redirection
	LLESS, // here doc
	PIPE,
}					t_token_type;

typedef struct s_cmd
{
	char			*cmd_name;
	char			**cmd_args;
	struct s_cmd	*next_cmd;
}					t_cmd;

typedef struct s_token
{
	int				token_id;
	char			*token_name;
	t_token_type	token_type;
	t_token_redir	token_redir;
	struct s_token	*next_token;
}					t_token;

typedef struct s_envar
{
	char			*key;
	char			*value;
	struct s_envar	*next;
}					t_envar;

typedef struct s_minishell
{
	t_token			*token_list;
	t_envar			*env_list;
	t_cmd			*cmd_list;
}					t_minishell;

bool				ft_parsing(t_minishell *minishell, char *input);

void				ft_append_token(t_minishell *minishell, t_token *new_token);
void				ft_free_token_list(t_minishell *minishell);
int					ft_token_redir(t_token_type type);
int					ft_last_token_id(t_minishell *minishell);

bool				ft_pipe(t_minishell *minishell, int *i);
bool				ft_great(t_minishell *minishell, int *i);
bool				ft_ggreat(t_minishell *minishell, int *i);
bool				ft_less(t_minishell *minishell, int *i);
bool				ft_lless(t_minishell *minishell, int *i);
bool				ft_word(t_minishell *minishell, char *input, int *i);
bool				ft_tokenization(t_minishell *minishell, char *input, int i);
bool				ft_create_output_token(t_minishell *minishell);
bool				ft_create_word_token(t_minishell *minishell, char *input);
bool				ft_create_hdoc_token(t_minishell *minishell);
bool				ft_create_append_token(t_minishell *minishell);
bool				ft_create_input_token(t_minishell *minishell);
bool				ft_create_pipe_token(t_minishell *minishell);

bool				ft_token_order(t_minishell *minishell);
bool				ft_check_pipe(t_minishell *minishell);
bool				ft_check_redir(t_minishell *minishell);

int					ft_wordlen(char *input);
bool				ft_space(char c);
bool				ft_notword(char c);

bool				ft_not_handling(char *input);
bool				ft_unclosed_quotes(char *input);
bool				ft_only_spaces(char *input);

void				ft_error(char *error_message);
void				ft_token_error(char *error_message);

bool				ft_envar_list(char **envp, t_minishell *minishell);
bool				ft_add_envar(t_minishell *minishell, char *key,
						char *value);
char				*ft_get_key(char *envp, char c);
char				*ft_get_value(char *envar, int start);

#endif