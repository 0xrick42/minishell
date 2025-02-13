/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:50:47 by aistierl          #+#    #+#             */
/*   Updated: 2024/05/20 15:48:05 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	limit;

	i = 0;
	while (dst[i] != '\0')
		i++;
	if (siz <= i)
		return (ft_strlen(src) + siz);
	else
	{
		limit = siz - 1 - i;
		j = 0;
		while (src[j] != '\0' && j < limit)
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
		return (i + ft_strlen(src));
	}
}
