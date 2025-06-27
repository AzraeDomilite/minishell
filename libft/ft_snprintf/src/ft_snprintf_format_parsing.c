/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_format_parsing.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:34:02 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 15:34:05 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

void	parse_length_modifier(t_format_info *info, const char **p)
{
	if (**p == 'h' || **p == 'l')
	{
		info->length_modifier = **p;
		(*p)++;
		if (info->length_modifier == 'l' && **p == 'l')
		{
			info->length_modifier = '2';
			(*p)++;
		}
	}
}

void	handle_format_synonym(t_format_info *info, char spec)
{
	if (spec == 'i')
		info->fmt_spec = 'd';
	else if (spec == 'D')
	{
		info->fmt_spec = 'd';
		info->length_modifier = 'l';
	}
	else if (spec == 'U')
	{
		info->fmt_spec = 'u';
		info->length_modifier = 'l';
	}
	else if (spec == 'O')
	{
		info->fmt_spec = 'o';
		info->length_modifier = 'l';
	}
	else
		info->fmt_spec = spec;
}

void	handle_char_string_format(t_format_info *info, t_arg_data *arg, \
								va_list ap)
{
	unsigned char	uchar_arg;
	int				j;

	info->length_modifier = '\0';
	info->zero_padding = 0;
	arg->str_arg_l = 1;
	if (info->fmt_spec == '%')
		arg->str_arg = &info->fmt_spec;
	else if (info->fmt_spec == 'c')
	{
		j = va_arg(ap, int);
		uchar_arg = (unsigned char)j;
		arg->str_arg = (const char *)&uchar_arg;
	}
	else if (info->fmt_spec == 's')
	{
		arg->str_arg = va_arg(ap, const char *);
		if (!arg->str_arg)
			arg->str_arg_l = 0;
		else
			handle_string_precision(info, arg);
	}
}

void	handle_unknown_format(t_format_info *info, t_arg_data *arg,
							const char **p)
{
	info->zero_padding = 0;
	info->justify_left = 1;
	info->min_field_width = 0;
	arg->str_arg = *p;
	arg->str_arg_l = 0;
	if (**p)
		arg->str_arg_l++;
}
