/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:40:20 by aistierl          #+#    #+#             */
/*   Updated: 2024/05/30 14:53:03 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*result;
	unsigned char	character;

	result = (unsigned char *)s;
	character = (unsigned char) c;
	if (n <= 0)
		return (NULL);
	if (character == '\0' && ft_strlen(s) < n)
		return (result + ft_strlen(s));
	else if (character == '\0' && ft_strlen(s) > n)
		return (NULL);
	else
	{
		i = 0;
		while (i < n)
		{
			if (result[i] == character)
				return (result + i);
			i++;
		}
		return (NULL);
	}
}
