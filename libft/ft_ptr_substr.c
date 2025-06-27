/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:25:03 by baschnit          #+#    #+#             */
/*   Updated: 2024/12/06 23:47:15 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief returns a substring starting with start and ending at end
 *
 * The function must be called with two iterators of the same C string and will
 * create a substring starting from start and ending and including end.
 *
 * If end lies before start an empty string will be returned. If begin or end
 * are the string end ('\0') a substring with just one terminal 0 character will
 * be returned.
 *
 * @param start pointer to the start of the substring
 * @param end pointer to the end of the substring
 * @return char* substring between start and end including end
*/
char	*ft_ptr_substr(const char *start, const char *end)
{
	char	*result;
	char	*temp;
	size_t	len;

	len = end - start + 2 - (!*end);
	if (len <= 0)
		len = 1;
	result = malloc(len);
	if (!result)
		return (NULL);
	temp = result;
	while (start <= end)
	{
		if (start == end && (!*end))
			break ;
		*result = *start;
		start++;
		result++;
	}
	*result = '\0';
	return (temp);
}
