/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:26:47 by aistierl          #+#    #+#             */
/*   Updated: 2024/05/30 16:16:56 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*haystack;
	char			*needle;

	i = 0;
	j = 0;
	haystack = (char *)big;
	needle = (char *)little;
	if (needle[j] == '\0')
		return (haystack);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + j] == needle[j] && needle[j] != '\0')
		{
			if ((i + j) >= len)
				return (NULL);
			j++;
		}
		if (needle[j] == '\0')
			return (haystack + i);
		i++;
		j = 0;
	}
	return (NULL);
}
