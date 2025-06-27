/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_parse_precision.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:18:19 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 19:18:31 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

static void	parse_precision_star(t_format_info *info, \
		const char **p, va_list ap)
{
	int	j;

	j = va_arg(ap, int);
	(*p)++;
	if (j >= 0)
		info->precision = j;
	else
	{
		info->precision_specified = 0;
		info->precision = 0;
	}
}

static void	parse_precision_digits(t_format_info *info, const char **p)
{
	unsigned int	uj;

	uj = **p - '0';
	(*p)++;
	while (isdigit((int)(**p)))
	{
		uj = 10 * uj + (unsigned int)(**p - '0');
		(*p)++;
	}
	info->precision = uj;
}

void	parse_precision(t_format_info *info, const char **p, va_list ap)
{
	if (**p == '.')
	{
		(*p)++;
		info->precision_specified = 1;
		if (**p == '*')
			parse_precision_star(info, p, ap);
		else if (isdigit((int)(**p)))
			parse_precision_digits(info, p);
	}
}
