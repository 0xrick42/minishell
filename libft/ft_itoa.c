/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:33:34 by aistierl          #+#    #+#             */
/*   Updated: 2024/05/31 18:14:53 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

int	intlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*negative_itoa(int n, char *string, int length)
{
	int	i;

	i = length - 1;
	string[0] = '-';
	n *= -1;
	while (i > 0)
	{
		string[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	string[length] = '\0';
	return (string);
}

char	*positive_itoa(int n, char *string, int length)
{
	int	i;

	i = length - 1;
	while (i > 0)
	{
		string[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	string[i] = n + '0';
	string[length] = '\0';
	return (string);
}

char	*ft_itoa(int n)
{
	char	*string;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	string = malloc((intlen(n) + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	if (n < 0)
		return (negative_itoa(n, string, intlen(n)));
	if (n > 9)
		return (positive_itoa(n, string, intlen(n)));
	string[intlen(n) - 1] = n + '0';
	string[intlen(n)] = '\0';
	return (string);
}
