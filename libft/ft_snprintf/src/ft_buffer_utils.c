/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:17:24 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 19:17:31 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

size_t	ft_numlen_base(unsigned long n, int base)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

static void	negative_itoa(int *n, unsigned int *num, int *neg)
{
	*neg = 0;
	if (*n < 0)
	{
		*neg = 1;
		*num = -*n;
	}
	else
		*num = *n;
}

size_t	ft_itoa_to_buf(int n, char *buf)
{
	size_t			len;
	size_t			pos;
	unsigned int	num;
	int				negative;

	negative_itoa(&n, &num, &negative);
	len = ft_numlen_base(num, 10) + negative;
	pos = len;
	buf[pos] = '\0';
	if (num == 0)
		buf[--pos] = '0';
	while (num > 0)
	{
		buf[--pos] = (num % 10) + '0';
		num /= 10;
	}
	if (negative)
		buf[0] = '-';
	return (len);
}

size_t	ft_utoa_to_buf(unsigned int n, char *buf)
{
	size_t	len;
	size_t	pos;

	len = ft_numlen_base(n, 10);
	pos = len;
	buf[pos] = '\0';
	if (n == 0)
		buf[--pos] = '0';
	while (n > 0)
	{
		buf[--pos] = (n % 10) + '0';
		n /= 10;
	}
	return (len);
}

size_t	ft_itoa_base_to_buf(unsigned long value, char *buf, \
			int base, int uppercase)
{
	size_t	len;
	size_t	pos;
	char	*symbols;

	if (uppercase)
		symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	else
		symbols = "0123456789abcdefghijklmnopqrstuvwxyz";
	if (base < 2 || base > 36)
		return (0);
	len = ft_numlen_base(value, base);
	pos = len;
	buf[pos] = '\0';
	if (value == 0)
		buf[--pos] = '0';
	while (value > 0)
	{
		buf[--pos] = symbols[value % base];
		value /= base;
	}
	return (len);
}
