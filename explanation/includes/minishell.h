/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:15:22 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/25 14:38:45 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** Required Standard Libraries
** - libft.h: Custom library with utility functions
** - define.h: Project-specific definitions and enums
** - Other standard C libraries for system calls and utilities
*/
# include "../libft/libft.h"
# include "define.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

/*
** Data Structures
*/

/*
** Command Structure
** Represents a single command in the shell
** - cmd_name: The name of the command to execute
** - cmd_args: Array of arguments (including the command name)
** - next_cmd: Pointer to the next command in a pipeline
*/
typedef struct s_cmd
{
    char            *cmd_name;
    char            **cmd_args;
    struct s_cmd    *next_cmd;
}   t_cmd;

/*
** Token Structure
** Represents a lexical token in the input
** - token_id: Unique identifier for the token
** - token_name: The actual string content of the token
** - token_type: Type of token (WORD, PIPE, etc.)
** - token_redir: Whether this token is part of a redirection
** - next_token: Pointer to the next token in the list
*/
typedef struct s_token
{
    int             token_id;
    char            *token_name;
    t_token_type    token_type;
    t_token_redir   token_redir;
    struct s_token  *next_token;
}   t_token;

/*
** Environment Variable Structure
** Represents a single environment variable
** - key: Name of the environment variable
** - value: Value of the environment variable
** - next: Pointer to the next environment variable
*/
typedef struct s_envar
{
    char            *key;
    char            *value;
    struct s_envar  *next;
}   t_envar;

/*
** Main Shell Structure
** Contains all the state information for the shell
** - token_list: List of tokens from current command
** - env_list: List of environment variables
** - cmd_list: List of commands to execute
** - exit_status: Status of the last executed command
*/
typedef struct s_minishell
{
    t_token         *token_list;
    t_envar         *env_list;
    t_cmd           *cmd_list;
    int             exit_status;
}   t_minishell;

/*
** Function Prototypes
*/

/* Error Handling Functions */
void    ft_error(char *message);

/* Parsing Functions */
bool    ft_parsing(t_minishell *minishell, char *input);
int     ft_wordlen(char *input);
bool    ft_space(char c);
bool    ft_notword(char c);
bool    ft_not_handling(char *input);
bool    ft_unclosed_quotes(char *input);
bool    ft_only_spaces(char *input);

/* String Manipulation Functions */
char    **ft_split_quotes(char const *s, char c);
void    ft_free_split(char **split, int size);
int     ft_count_words(char const *s, char c);
char    *ft_get_word(char const *s, char c, int *i);
char    *ft_get_quoted_word(char const *s, int *i);
char    *ft_get_normal_word(char const *s, char c, int *i);

/* Token Handling Functions */
void    ft_append_token(t_minishell *minishell, t_token *new_token);
void    ft_free_token_list(t_minishell *minishell);
int     ft_token_redir(t_token_type type);
int     ft_last_token_id(t_minishell *minishell);
bool    ft_tokenization(t_minishell *minishell, char *input, int i);

/* Token Creation Functions */
bool    ft_create_output_token(t_minishell *minishell);
bool    ft_create_word_token(t_minishell *minishell, char *input);
bool    ft_create_hdoc_token(t_minishell *minishell);
bool    ft_create_append_token(t_minishell *minishell);
bool    ft_create_input_token(t_minishell *minishell);
bool    ft_create_pipe_token(t_minishell *minishell);

/* Token Operation Functions */
bool    ft_pipe(t_minishell *minishell, int *i);
bool    ft_great(t_minishell *minishell, int *i);
bool    ft_ggreat(t_minishell *minishell, int *i);
bool    ft_less(t_minishell *minishell, int *i);
bool    ft_lless(t_minishell *minishell, int *i);
bool    ft_word(t_minishell *minishell, char *input, int *i);

/* Token Validation Functions */
bool    ft_token_order(t_minishell *minishell);
bool    ft_check_pipe(t_minishell *minishell);
bool    ft_check_redir(t_minishell *minishell);

/* Token Handler Functions */
bool    ft_handle_pipe_token(t_minishell *minishell, char *input, int *i);
bool    ft_handle_great_token(t_minishell *minishell, char *input, int *i);
bool    ft_handle_less_token(t_minishell *minishell, char *input, int *i);

/* Environment Variable Functions */
bool    ft_envar_list(char **envp, t_minishell *minishell);
bool    ft_add_envar(t_minishell *minishell, char *key, char *value);
char    *ft_get_key(char *envp, char c);
char    *ft_get_value(char *envar, int start);

/* Command Handling Functions */
bool    ft_cmd_struct(char *input, t_minishell *minishell);
bool    ft_cmd_list(char *cmd_cell, t_minishell *minishell);
char    **ft_split_cmd_args(char *cmd_cell);
void    ft_free_cmd_list(t_cmd *cmd_list);
void    ft_free_table(char **table);

/* Command List Management Functions */
bool    ft_create_cmd(t_minishell *minishell, char **cmd_args);
bool    ft_create_cmd_list(t_minishell *minishell, char **cmd_cells);

/* Environment Management Functions */
t_envar *ft_create_env_list(char **envp);
void    ft_add_envar(t_minishell *minishell, char *key, char *value);
char    *ft_get_env_value(t_minishell *minishell, char *var_name);

/* String Processing Functions */
bool    ft_init_split(char const *s, char c, char ***split, int *words);
bool    ft_process_word(char **split, char const *s, char c, int *pos);
char    *ft_remove_quotes(char *str);
bool    ft_in_quotes(char *str, int pos);

#endif 