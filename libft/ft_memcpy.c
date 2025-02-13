/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:40:08 by aistierl          #+#    #+#             */
/*   Updated: 2024/05/23 19:19:24 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*point_a;
	unsigned char	*point_b;
	unsigned int	i;

	if (src == NULL && dst == NULL)
		return (dst);
	point_a = (unsigned char *)src;
	point_b = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		point_b[i] = point_a[i];
		i++;
	}
	return (dst);
}
