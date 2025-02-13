/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:10:59 by aistierl          #+#    #+#             */
/*   Updated: 2024/06/10 17:18:39 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (new == NULL)
		return ;
	if (*lst != NULL)
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	else
		*lst = new;
}
