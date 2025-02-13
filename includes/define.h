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

# define SUCCESS 0
# define ERROR 1

/* Token types */
typedef enum e_token_type
{
	WORD,
	GREAT,
	GGREAT,
	LESS,
	LLESS,
	PIPE,
}	t_token_type;

typedef enum e_token_redir
{
	NONE,
	REDIR,
}	t_token_redir;

#endif 