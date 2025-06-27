/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:58:40 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 13:59:00 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

int	isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

static void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*t;

	i = 0;
	t = (char *) s;
	while (i < n)
	{
		*t = c;
		t++;
		i++;
	}
	return (s);
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = (char *) dest;
	s = (char *) src;
	while (i < n)
	{
		*d = *s;
		d++;
		s++;
		i++;
	}
	return (dest);
}

void	fast_memcpy(void *d, const void *s, size_t n)
{
	register size_t		nn;
	register char		*dd;
	register const char	*ss;

	nn = (size_t)(n);
	if (nn >= BREAKEVEN_POINT)
	{
		ft_memcpy(d, s, nn);
	}
	else if (nn > 0)
	{
		dd = (char *)d;
		ss = (const char *)s;
		while (nn--)
			*dd++ = *ss++;
	}
}

void	fast_memset(void *d, int c, size_t n)
{
	register size_t	nn;
	register char	*dd;
	register int	cc;

	nn = (size_t)(n);
	if (nn >= BREAKEVEN_POINT)
	{
		ft_memset(d, c, nn);
	}
	else if (nn > 0)
	{
		dd = (char *)d;
		cc = (int)c;
		while (nn--)
			*dd++ = cc;
	}
}
