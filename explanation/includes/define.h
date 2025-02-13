/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
** Return Values
** These define the standard return values for functions
** SUCCESS (0): Operation completed successfully
** ERROR (1): Operation failed
*/
# define SUCCESS 0
# define ERROR 1

/*
** Token Types Enumeration
** Defines the different types of tokens that can be recognized:
** - WORD: Regular text (commands, arguments, filenames)
** - GREAT: Output redirection (>)
** - GGREAT: Append output redirection (>>)
** - LESS: Input redirection (<)
** - LLESS: Here document (<<)
** - PIPE: Command pipeline (|)
*/
typedef enum e_token_type
{
    WORD,       /* Regular text token */
    GREAT,      /* > redirection */
    GGREAT,     /* >> redirection */
    LESS,       /* < redirection */
    LLESS,      /* << here document */
    PIPE,       /* | pipeline */
}   t_token_type;

/*
** Token Redirection Type
** Indicates whether a token is part of a redirection operation:
** - NONE: Not a redirection
** - REDIR: Is a redirection operator
*/
typedef enum e_token_redir
{
    NONE,       /* Not a redirection */
    REDIR,      /* Is a redirection */
}   t_token_redir;

#endif 