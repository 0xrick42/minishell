/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:50:52 by aistierl          #+#    #+#             */
/*   Updated: 2024/05/30 16:19:56 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	char	*convert;
	int		i;
	int		sign;
	int		digit;

	i = 0;
	sign = 1;
	digit = 0;
	convert = (char *)nptr;
	while ((convert[i] >= '\t' && convert[i] <= '\r') || convert[i] == ' ')
		i++;
	if (convert[i] == '-' || convert[i] == '+')
	{
		if (convert[i] == '-')
			sign *= -1;
		i++;
	}
	if (convert[i] == '-' || convert[i] == '+')
		return (0);
	while (convert[i] >= '0' && convert[i] <= '9')
	{
		digit = digit * 10 + (convert[i] - '0');
		i++;
	}
	return (digit * sign);
}
