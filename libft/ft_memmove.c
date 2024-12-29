/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:28:48 by aistierl          #+#    #+#             */
/*   Updated: 2024/05/29 17:27:18 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int	comp_adress(unsigned char *src, unsigned char *dst, size_t limit)
{
	while ((limit - 1) > 0)
	{
		if (&src[limit - 1] == &dst[0])
			return (1);
		limit--;
	}
	return (0);
}

void	ft_strcpy_modif(unsigned char *dst, unsigned char *src, size_t siz)
{
	unsigned int	i;

	i = 0;
	while (i < siz)
	{
		dst[i] = src[i];
		i++;
	}
}

void	ft_strcpy_rev(unsigned char *dst, unsigned char *src, size_t siz)
{
	unsigned int	i;

	i = siz - 1;
	while (i > 0)
	{
		dst[i] = src[i];
		i--;
	}
	dst[0] = src[0];
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*point_a;
	unsigned char	*point_b;

	if (src == NULL && dst == NULL)
		return (dst);
	if (n == 0)
		return (dst);
	point_a = (unsigned char *)src;
	point_b = (unsigned char *)dst;
	if (comp_adress(point_a, point_b, n) == 1)
		ft_strcpy_rev(point_b, point_a, n);
	if (comp_adress(point_a, point_b, n) != 1)
		ft_strcpy_modif(point_b, point_a, n);
	return (dst);
}
