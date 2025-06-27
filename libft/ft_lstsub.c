/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:40:22 by blucken           #+#    #+#             */
/*   Updated: 2025/05/05 11:40:50 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

/**
 * @brief copy a list element
 *
 * Will copy a list element including a copy of its content by using the
 * supplied function pointer to a content copy function. Returns a pointer to
 * the newly created list element.
 *
 * @param src		list element to copy
 * @param copy		function to copy the list element's content
 * @return			pointer to the newly created copy of the src list element
*/
t_list	*ft_lstelem_copy(t_list *src, void *(*copy)(void *))
{
	void	*new;
	t_list	*lnew;

	if (!set(&lnew, malloc(sizeof(t_list))))
		return (NULL);
	lnew->next = NULL;
	if (!set(&new, copy(src->content)))
		return (free(lnew), NULL);
	lnew->content = new;
	return (lnew);
}

/**
 * @brief creates a copy of a linked list from pointers left to right excluding
 * right
 *
 * Loops through a linked list starting with the element left copying each list
 * element by using the function ft_lstelem_copy().
 *
 * If left is a NULL pointer or right is not a follow up element of left, a NULL
 * pointer is returned. Else, a pointer to the newly created copy of the sub
 * list is returned.
 *
 * If right is a NULL pointer, the whole list, starting at left, will be copied.
 *
 *
 * @param left	pointer to the list element to start with
 * @param right	pointer to the list element to end the list with
 * @param copy	function to copy a list element's content
 * @param del	function to delete a lists element's content
 * @return		returns a pointer to the first element in the copied sub list
*/
t_list	*ft_lstsub(t_list *left, t_list *right, \
		void *(*copy)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*lnew;

	new = left;
	while (right && new)
	{
		if (new == right)
			break ;
		if (!new->next)
			return (NULL);
		new = new->next;
	}
	new = NULL;
	while (left && left != right)
	{
		if (!set(&(lnew), ft_lstelem_copy(left, copy)))
			return (ft_lstclear(&new, del), NULL);
		ft_lstadd_back(&new, lnew);
		left = left->next;
	}
	return (new);
}
