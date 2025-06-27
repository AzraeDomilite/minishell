/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_core.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:41:06 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 15:41:13 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

void	prepare_format_info(t_format_info *info, t_arg_data *arg,
						const char **p, va_list ap)
{
	init_format_info(info);
	arg->zeros_to_pad = 0;
	parse_flags(info, p);
	parse_field_width(info, p, ap);
	parse_precision(info, p, ap);
	parse_length_modifier(info, p);
	handle_format_synonym(info, **p);
}

void	process_format_specifier(t_output_buffer *out, const char **p,
							va_list ap)
{
	t_format_info	info;
	t_arg_data		arg;
	char			tmp[32];

	(*p)++;
	prepare_format_info(&info, &arg, p, ap);
	if (info.fmt_spec == '%' || info.fmt_spec == 'c' || info.fmt_spec == 's')
	{
		handle_char_string_format(&info, &arg, ap);
	}
	else if (info.fmt_spec == 'd' || info.fmt_spec == 'u' || \
			info.fmt_spec == 'o' || info.fmt_spec == 'x' || \
			info.fmt_spec == 'X' || info.fmt_spec == 'p')
	{
		handle_numeric_format(&info, &arg, ap, tmp);
	}
	else
		handle_unknown_format(&info, &arg, p);
	if (**p)
		(*p)++;
	handle_left_padding(&info, &arg, out);
	handle_zero_padding(&arg, out);
	insert_formatted_string(&arg, out);
	handle_right_padding(&info, &arg, out);
}

int	ft_snprintf(char *str, size_t str_m, const char *fmt, ...)
{
	va_list	ap;
	int		str_l;

	va_start(ap, fmt);
	str_l = ft_vsnprintf(str, str_m, fmt, ap);
	va_end(ap);
	return (str_l);
}

int	ft_vsnprintf(char *str, size_t str_m, const char *fmt, va_list ap)
{
	t_output_buffer	out;
	const char		*p;

	out.str = str;
	out.str_m = str_m;
	out.str_l = 0;
	if (fmt)
		p = fmt;
	else
		p = "";
	while (*p)
	{
		if (*p != '%')
			process_non_format_chars(&out, &p);
		else
			process_format_specifier(&out, &p, ap);
	}
	if (str_m > 0)
	{
		if (out.str_l < str_m)
			str[out.str_l] = '\0';
		else
			str[str_m - 1] = '\0';
	}
	return ((int)out.str_l);
}
