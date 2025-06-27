/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:37:40 by blucken           #+#    #+#             */
/*   Updated: 2025/05/05 11:37:57 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief removes pair of quotes on first and last position of the str
 * 
 * The function will either remove a pair of double quotes or a pair 
 * of single quotes, if they are on the first and last position of the string.
 * Otherwise a duplicate of the original string will be returned.
 * 
 * @param start 		str, which might be surrounded by a pair of quotes
 * @return char* 	newly allocated str without quotes
 */
char	*ft_remove_quotes(char *start)
{
	char	*end;

	end = start;
	while (*end)
		end++;
	if (start == end)
		return (ft_strdup(""));
	end--;
	if ((*start == '"' && *end == '"') || (*start == '\'' && *end == '\''))
	{
		if (start == end)
			return (ft_strdup(""));
		else
			return (ft_ptr_substr(start + 1, end - 1));
	}
	return (ft_strdup(start));
}
