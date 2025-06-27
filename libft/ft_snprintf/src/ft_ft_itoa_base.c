/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_itoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:57:48 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 13:57:49 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

static size_t	ft_numlen(unsigned long n, int base)
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

static char	*allocate_itoa_base_str(int value, \
	int base, size_t *len, int *negative)
{
	unsigned int	num;

	*negative = 0;
	if (base == 10 && value < 0)
		*negative = 1;
	num = value;
	if (*negative)
		num = -value;
	*len = ft_numlen(num, base) + *negative;
	return ((char *)malloc(sizeof(char) * (*len + 1)));
}

static void	fill_itoa_base_str(char *str, unsigned int num, \
	int base, size_t len)
{
	char	*symbols;

	symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	str[len] = '\0';
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--len] = symbols[num % base];
		num /= base;
	}
}

char	*ft_itoa_base(int value, int base)
{
	char			*str;
	size_t			len;
	unsigned int	num;
	int				negative;

	if (base < 2 || base > 36)
		return (NULL);
	str = allocate_itoa_base_str(value, base, &len, &negative);
	if (!str)
		return (NULL);
	if (negative)
		str[0] = '-';
	num = value;
	if (negative)
		num = -value;
	fill_itoa_base_str(str, num, base, len);
	return (str);
}
