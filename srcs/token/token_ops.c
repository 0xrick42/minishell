/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:15:22 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/28 11:45:38 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_pipe(t_minishell *minishell, int *i)
{
	if (!ft_create_pipe_token(minishell))
		return (ft_free_token_list(minishell), false);
	*i += 1;
	return (true);
}

bool	ft_word(t_minishell *minishell, char *input, int *i)
{
	if (!ft_create_word_token(minishell, input + *i))
		return (ft_free_token_list(minishell), false);
	if ((input[*i] == '"' || input[*i] == '\''))
		*i += ft_wordlen(input + *i) + 2;
	else
		*i += ft_wordlen(input + *i);
	return (true);
}

bool	ft_great(t_minishell *minishell, int *i)
{
	if (!ft_create_output_token(minishell))
		return (ft_free_token_list(minishell), false);
	*i += 1;
	return (true);
}

bool	ft_ggreat(t_minishell *minishell, int *i)
{
	if (!ft_create_append_token(minishell))
		return (ft_free_token_list(minishell), false);
	*i += 2;
	return (true);
}

bool	ft_less(t_minishell *minishell, int *i)
{
	if (!ft_create_input_token(minishell))
		return (ft_free_token_list(minishell), false);
	*i += 1;
	return (true);
}
