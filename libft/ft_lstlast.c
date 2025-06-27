/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:19 by baschnit          #+#    #+#             */
/*   Updated: 2024/09/21 13:09:19 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

/**
 * @brief return the element previous of the last element in list
 * 
 * Returns the element previous of the last element in list. 
 * Will return NULL if list is empty or has only one element.
 * 
 * @param somewhere	a list element to start at
 * @return			returns the element previous to the last element in the list
 */
t_list	*ft_lstprevious_last(t_list *somewhere)
{
	t_list	*previous;

	previous = NULL;
	if (!somewhere)
		return (NULL);
	while (somewhere->next != NULL)
	{
		previous = somewhere;
		somewhere = somewhere->next;
	}
	return (previous);
}

/**
 * @brief return the last element in list
 * 
 * Returns the last element in list or NULL if list is empty
 * 
 * @param somewhere	a list element to start at
 * @return			returns the last element in the list
 */
t_list	*ft_lstlast(t_list *somewhere)
{
	if (!somewhere)
		return (NULL);
	while (somewhere->next != NULL)
	{
		somewhere = somewhere->next;
	}
	return (somewhere);
}
