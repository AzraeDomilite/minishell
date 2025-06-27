/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:23:29 by baschnit          #+#    #+#             */
/*   Updated: 2024/12/11 00:10:13 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "libft.h"

/**
 * @brief removes white space (only space and tab) from beginning and end of str
 *
 * Takes a str, scans for white space at the beginning and end of the str and
 * returns a substring without the white space.
 *
 * @param str
 * @return char*
*/
char	*ft_strip(const char *str)
{
	size_t	len;
	char	*end;

	while (ft_isblank(*str))
		str++;
	len = ft_strlen(str);
	if (len == 0)
		return (ft_strdup(""));
	end = (char *) str + len - 1;
	while (ft_isblank(*end) && end != str)
		end--;
	return (ft_ptr_substr(str, end));
}
