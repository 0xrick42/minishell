/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:15:42 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/26 21:38:15 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_init_split(char const *s, char c, char ***split, int *words)
{
	if (!s)
		return (false);
	*words = ft_count_words(s, c);
	*split = malloc(sizeof(char *) * (*words + 1));
	if (!*split)
		return (false);
	return (true);
}
