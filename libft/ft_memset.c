/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:51:03 by aistierl          #+#    #+#             */
/*   Updated: 2024/05/30 18:32:10 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	character;
	unsigned char	*p;

	character = (unsigned char)c;
	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = character;
		i++;
	}
	return (s);
}
