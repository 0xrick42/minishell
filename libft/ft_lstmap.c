/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistierl <aistierl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:09:55 by aistierl          #+#    #+#             */
/*   Updated: 2024/06/11 16:09:09 by aistierl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	void	*temporary;
	t_list	*head;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	head = NULL;
	while (lst != NULL)
	{
		temporary = f(lst->content);
		if (!temporary)
			return (ft_lstclear(&head, del), NULL);
		new = ft_lstnew(temporary);
		if (new == NULL)
		{
			free(temporary);
			return (ft_lstclear(&head, del), NULL);
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
