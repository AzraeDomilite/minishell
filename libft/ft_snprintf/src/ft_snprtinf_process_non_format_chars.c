/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprtinf_process_non_format_chars.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:39:32 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 15:40:15 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

static size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		s++;
		count++;
	}
	return (count);
}

static char	*ft_strchr(const char *s, int c)
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

void	process_non_format_chars(t_output_buffer *out, const char **p)
{
	const char	*q;
	size_t		n;
	size_t		avail;

	q = ft_strchr(*p + 1, '%');
	if (!q)
		n = ft_strlen(*p);
	else
		n = (size_t)(q - *p);
	if (out->str_l < out->str_m)
	{
		avail = out->str_m - out->str_l;
		if (n > avail)
			n = avail;
		fast_memcpy(out->str + out->str_l, *p, n);
	}
	*p += n;
	out->str_l += n;
}
