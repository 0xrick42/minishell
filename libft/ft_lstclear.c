/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:45:45 by aistierl          #+#    #+#             */
/*   Updated: 2024/06/11 16:11:07 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temporary;

	if (del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		del(current->content);
		temporary = current->next;
		free(current);
		current = temporary;
	}
	*lst = NULL;
}
