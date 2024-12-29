/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:29:00 by aistierl          #+#    #+#             */
/*   Updated: 2024/06/25 15:00:24 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			*result;
	int				character;

	result = (char *)s;
	character = c % 256;
	if (character == '\0')
		return (result + ft_strlen(s));
	else
	{
		i = 0;
		while (i < ft_strlen(s))
		{
			if (result[i] == character)
				return (result + i);
			i++;
		}
		return (NULL);
	}
}
