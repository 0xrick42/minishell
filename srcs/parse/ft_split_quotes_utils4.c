/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_utils4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:00:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/01/28 00:00:00 by aistierl         ###   ########.fr       */
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
