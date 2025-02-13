/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:10:22 by aistierl          #+#    #+#             */
/*   Updated: 2024/05/27 17:43:02 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char				*new;
	unsigned int		i;

	new = ft_strdup(s);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(new))
	{
		new[i] = f(i, new[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
