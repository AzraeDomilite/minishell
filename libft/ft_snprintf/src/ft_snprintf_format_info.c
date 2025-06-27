/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_format_info.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:44:22 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:44:25 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

void	init_format_info(t_format_info *info)
{
	info->min_field_width = 0;
	info->precision = 0;
	info->zero_padding = 0;
	info->precision_specified = 0;
	info->justify_left = 0;
	info->alternate_form = 0;
	info->force_sign = 0;
	info->space_for_positive = 1;
	info->length_modifier = '\0';
	info->fmt_spec = '\0';
}

void	handle_flag(t_format_info *info, char flag)
{
	if (flag == '0')
		info->zero_padding = 1;
	else if (flag == '-')
		info->justify_left = 1;
	else if (flag == '+')
	{
		info->force_sign = 1;
		info->space_for_positive = 0;
	}
	else if (flag == ' ')
		info->force_sign = 1;
	else if (flag == '#')
		info->alternate_form = 1;
}

void	parse_flags(t_format_info *info, const char **p)
{
	while (**p == '0' || **p == '-' || **p == '+' || \
			**p == ' ' || **p == '#' || **p == '\'')
	{
		handle_flag(info, **p);
		(*p)++;
	}
}
