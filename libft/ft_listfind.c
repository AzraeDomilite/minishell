/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listfind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:31:15 by baschnit          #+#    #+#             */
/*   Updated: 2025/02/14 11:46:18 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Finds the first list element in a list by comparing the content
 *
 * Will return the first list element in the list start where the function comp
 * yields 1 in comparing the list content and the needle.
 *
 * @param start		beginning of the list to scan
 * @param needle	pointer to a content to compare to
 * @param comp		function to compare the list content and the needle
 * @return			returns a pointer to the found element in start or
 * NULL if no element compared successfully
*/
t_list	*ft_lstfind(t_list *start, void *needle, int (comp)(void *, void *))
{
	while (start)
	{
		if (comp(start->content, needle))
			return (start);
		start = start->next;
	}
	return (NULL);
}

/**
 * @brief Finds the first list element in a list by comparing the content to an
 * array of needles
 *
 * Will return the first list element in the list start where the function comp
 * yields 1 in comparing the list content to every needle in the array of
 * needles.
 *
 * @param start		beginning of the list to scan
 * @param needles	array of needles to compare the list content to
 * @param comp		function to compare the list content and the needle
 * @return			returns a pointer to the found element in start or
 * NULL if no element compared successfully
*/
t_list	*ft_lstfinds(t_list *start, void *needles[], int (comp)(void *, void *))
{
	void	**begin;

	while (start)
	{
		begin = needles;
		while (begin)
		{
			if (comp(start->content, *begin))
				return (start);
			begin++;
		}
		start = start->next;
	}
	return (NULL);
}
