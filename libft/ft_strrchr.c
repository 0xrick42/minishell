/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:45:09 by aistierl          #+#    #+#             */
/*   Updated: 2024/05/30 14:26:30 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int			i;
	char					*result;
	unsigned char			character;

	character = (unsigned char) c;
	result = (char *)s;
	if (character == '\0')
		return (result + ft_strlen(s));
	if (result[0] == '\0' && character != '\0')
		return (NULL);
	i = ft_strlen(s) - 1;
	while (i > 0)
	{
		if (result[i] == character)
			return (result + i);
		i--;
	}
	if (result[0] == character)
		return (result);
	return (NULL);
}
