/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprtinf_string_precision.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:18:09 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 19:18:15 by blucken          ###   ########.fr       */
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

static void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*t;
	unsigned char	a;
	size_t			i;

	a = (unsigned char) c;
	i = 0;
	t = (unsigned char *) s;
	while (i < n)
	{
		if (a == *t)
			return (t);
		t++;
		i++;
	}
	return (NULL);
}

void	handle_string_precision(t_format_info *info, t_arg_data *arg)
{
	const char	*q;
	size_t		max_len;

	if (!info->precision_specified)
		arg->str_arg_l = ft_strlen(arg->str_arg);
	else if (info->precision == 0)
		arg->str_arg_l = 0;
	else
	{
		if (info->precision <= 0x7fffffff)
			max_len = info->precision;
		else
			max_len = 0x7fffffff;
		q = ft_memchr(arg->str_arg, '\0', max_len);
		if (!q)
			arg->str_arg_l = info->precision;
		else
			arg->str_arg_l = (size_t)(q - arg->str_arg);
	}
}
