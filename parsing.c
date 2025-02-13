/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:03:52 by aistierl          #+#    #+#             */
/*   Updated: 2025/02/13 16:55:00 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *error_message)
{
	printf("Minishell: %s\n", error_message);
	return ;
}

bool	ft_tokenization(t_minishell *minishell, char *input, int i)
{	
	while (input[i] != '\0')
	{
		while (ft_space(input[i]))
			i++;
		if (!ft_strncmp(input + i, "|", 1) && !ft_pipe(minishell, &i))
			return (false);
		else if (!ft_strncmp(input + i, ">>", 2) && !ft_ggreat(minishell, &i))
			return (false);
		else if (!ft_strncmp(input + i, "<<", 2) && !ft_lless(minishell, &i))
			return (false);
		else if (!ft_strncmp(input + i, ">", 1) && !ft_great(minishell, &i))
			return (false);
		else if (!ft_strncmp(input + i, "<", 1) && !ft_less(minishell, &i))
			return (false);
		else if (!ft_space(input[i]) && !ft_notword(input[i])
			&& input[i] && !ft_word(minishell, input, &i))
			return (false);
	}
	return (true);
}

bool	ft_token_order(t_minishell *minishell)
{
	if (!ft_check_pipe(minishell))
		return (false);
	if (!ft_check_redir(minishell))
		return (false);
	return (true);
}

bool	ft_parsing(t_minishell *minishell, char *input)
{
	if (!ft_not_handling(input))
		return (false);
	if (!ft_unclosed_quotes(input))
		return (false);
	if (!ft_tokenization(minishell, input, 0))
		return (false);
	if (!ft_token_order(minishell))
		return (false);
	return (true);
}

// not interpreted:
// unclosed single/double quotes
// backslash \ or semicolon ; >>> a voir pour \ avant caractere special
// parenthesis () {} [] and & (not in subject)
// wildcards *, &&, || (bonus)