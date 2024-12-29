/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:33:38 by aistierl          #+#    #+#             */
/*   Updated: 2024/06/02 17:04:25 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	comp_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strndup_modif(const char *s, unsigned int n)
{
	char						*dest;
	unsigned int				i;

	dest = malloc(n + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strtrim(const char *s1, const char *set)
{	
	unsigned int				trim_start;
	unsigned int				trim_end;
	unsigned int				new_length;
	unsigned int				i;

	if (s1[0] == '\0')
		return (ft_strdup(s1));
	trim_start = 0;
	while (s1 && comp_set(s1[trim_start], set) == 1)
		trim_start++;
	trim_end = 0;
	i = ft_strlen(s1) - 1;
	while (i > trim_start && comp_set(s1[i], set) == 1)
	{
		trim_end++;
		i--;
	}
	new_length = ft_strlen(s1) - (trim_start + trim_end);
	return (ft_strndup_modif(s1 + trim_start, new_length));
}
