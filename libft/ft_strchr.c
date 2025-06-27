/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:59:38 by blucken           #+#    #+#             */
/*   Updated: 2024/12/12 16:59:38 by blucken          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char	a;

	a = (unsigned char) c;
	while (*s)
	{
		if (a == *s)
			return ((char *) s);
		s++;
	}
	if (!*s && a == '\0')
		return ((char *) s);
	return (NULL);
}
