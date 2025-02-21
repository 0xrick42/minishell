/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:15:42 by ykhomsi          #+#    #+#             */
/*   Updated: 2025/01/30 22:35:18 by ykhomsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	ft_is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*ft_get_var_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	(*i)++;
	start = *i;
	while (str[*i] && ft_is_var_char(str[*i]))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (NULL);
	return (var_name);
}

char	*ft_join_expanded(char *str1, char *str2)
{
	char	*result;

	if (!str1 || !str2)
		return (NULL);
	result = ft_strjoin(str1, str2);
	free(str1);
	return (result);
}

void	ft_skip_quotes(char *str, int *i, char quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
}

int	ft_count_dollars(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !ft_in_quotes(str, i))
			count++;
		i++;
	}
	return (count);
}
