/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:29:12 by baschnit          #+#    #+#             */
/*   Updated: 2024/12/07 22:43:56 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

void	ft_lstremove(t_list *to_remove, t_list **list, void (*del)(void*))
{
	t_list	*previous;

	previous = *list;
	if (previous == to_remove)
	{
		*list = previous->next;
		del(to_remove->content);
		free(to_remove);
		return ;
	}
	while (previous && previous->next != to_remove)
		previous = previous->next;
	if (!previous)
		return ;
	previous->next = to_remove->next;
	del(to_remove->content);
	free(to_remove);
}
