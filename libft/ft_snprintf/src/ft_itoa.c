/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:59:00 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 13:59:01 by blucken          ###   ########.fr       */
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

static char	*allocate_itoa_str(int n, size_t *len, int *negative)
{
	unsigned int	num;

	*negative = 0;
	if (n < 0)
		*negative = 1;
	num = n;
	if (n < 0)
		num = -n;
	*len = ft_numlen(num, 10) + *negative;
	return ((char *)malloc(sizeof(char) * (*len + 1)));
}

static void	fill_itoa_str(char *str, unsigned int num, size_t len, int negative)
{
	if (negative)
		str[0] = '-';
	str[len] = '\0';
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	unsigned int	num;
	int				negative;

	str = allocate_itoa_str(n, &len, &negative);
	if (!str)
		return (NULL);
	num = n;
	if (n < 0)
		num = -n;
	fill_itoa_str(str, num, len, negative);
	return (str);
}
