/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_parse_field_width.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:17:36 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 19:17:41 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

static void	parse_field_width_star(t_format_info *info, \
		const char **p, va_list ap)
{
	int	j;

	(*p)++;
	j = va_arg(ap, int);
	if (j >= 0)
		info->min_field_width = j;
	else
	{
		info->min_field_width = -j;
		info->justify_left = 1;
	}
}

static void	parse_field_width_digits(t_format_info *info, const char **p)
{
	unsigned int	uj;

	uj = **p - '0';
	(*p)++;
	while (isdigit((int)(**p)))
	{
		uj = 10 * uj + (unsigned int)(**p - '0');
		(*p)++;
	}
	info->min_field_width = uj;
}

void	parse_field_width(t_format_info *info, const char **p, va_list ap)
{
	if (**p == '*')
		parse_field_width_star(info, p, ap);
	else if (isdigit((int)(**p)))
		parse_field_width_digits(info, p);
}
