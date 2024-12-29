/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:48 by aistierl          #+#    #+#             */
/*   Updated: 2024/12/29 19:51:38 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include "./libft/libft.h"

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

#endif