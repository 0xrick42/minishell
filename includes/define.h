/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:20:33 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/25 15:42:18 by ykhomsi         ###   ########.fr       */
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