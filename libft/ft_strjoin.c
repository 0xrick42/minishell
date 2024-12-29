/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:48:13 by aistierl          #+#    #+#             */
/*   Updated: 2024/05/27 19:15:51 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int		i;
	unsigned int		j;
	char				*new;

	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (s1[i] != '\0')
		{
			new[i] = s1[i];
			i++;
		}
		j = 0;
		while (s2[j] != '\0')
		{
			new[i + j] = s2[j];
			j++;
		}
		new[i + j] = '\0';
		return (new);
	}
}
