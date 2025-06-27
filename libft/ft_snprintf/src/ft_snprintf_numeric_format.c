/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_numeric_format.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:19:23 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 19:20:30 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

void	format_numeric_value(t_format_info *info, t_arg_data *arg, \
						union u_value *value, char *tmp)
{
	if (info->fmt_spec == 'p')
		format_numeric_arg(info, tmp, &arg->str_arg_l, &value->pval);
	else if (info->fmt_spec == 'd')
	{
		if (info->length_modifier == '\0' || info->length_modifier == 'h')
			format_numeric_arg(info, tmp, &arg->str_arg_l, &value->ival);
		else if (info->length_modifier == 'l')
			format_numeric_arg(info, tmp, &arg->str_arg_l, &value->lval);
		else
			format_numeric_arg(info, tmp, &arg->str_arg_l, &value->llval);
	}
	else
	{
		if (info->length_modifier == '\0' || info->length_modifier == 'h')
			format_numeric_arg(info, tmp, &arg->str_arg_l, &value->uival);
		else if (info->length_modifier == 'l')
			format_numeric_arg(info, tmp, &arg->str_arg_l, &value->ulval);
		else
			format_numeric_arg(info, tmp, &arg->str_arg_l, &value->ullval);
	}
}

void	calculate_padding(t_format_info *info, t_arg_data *arg, char *tmp)
{
	size_t	num_of_digits;
	int		n;

	num_of_digits = arg->str_arg_l - arg->zero_padding_insertion_ind;
	if (info->alternate_form && info->fmt_spec == 'o' && \
		!(arg->zero_padding_insertion_ind < arg->str_arg_l && \
		tmp[arg->zero_padding_insertion_ind] == '0'))
	{
		if (!info->precision_specified || info->precision < num_of_digits + 1)
		{
			info->precision = num_of_digits + 1;
			info->precision_specified = 1;
		}
	}
	if (num_of_digits < info->precision)
		arg->zeros_to_pad = info->precision - num_of_digits;
	if (!info->justify_left && info->zero_padding)
	{
		n = info->min_field_width - (arg->str_arg_l + arg->zeros_to_pad);
		if (n > 0)
			arg->zeros_to_pad += n;
	}
}

int	handle_numeric_format(t_format_info *info, t_arg_data *arg, va_list ap,
						char *tmp)
{
	int				arg_sign;
	union u_value	value;

	arg_sign = 0;
	if (info->fmt_spec == 'p')
		set_numeric_arg_pointer(info, &value, &arg_sign, ap);
	else if (info->fmt_spec == 'd')
		set_numeric_arg_signed(info, &value, &arg_sign, ap);
	else
		set_numeric_arg_unsigned(info, &value, &arg_sign, ap);
	arg->str_arg = tmp;
	arg->str_arg_l = 0;
	if (info->precision_specified)
		info->zero_padding = 0;
	handle_sign_and_alt_form(info, arg, arg_sign, tmp);
	if (!info->precision_specified)
		info->precision = 1;
	if (!(info->precision == 0 && arg_sign == 0))
	{
		format_numeric_value(info, arg, &value, tmp);
		handle_special_padding_cases(arg, tmp);
	}
	calculate_padding(info, arg, tmp);
	return (arg_sign);
}

void	handle_right_padding(t_format_info *info, t_arg_data *arg, \
							t_output_buffer *out)
{
	int		n;
	size_t	avail;
	size_t	padding_size;

	if (info->justify_left)
	{
		n = info->min_field_width - (arg->str_arg_l + arg->zeros_to_pad);
		if (n > 0)
		{
			if (out->str_l < out->str_m)
			{
				avail = out->str_m - out->str_l;
				padding_size = (size_t)n;
				if (padding_size > avail)
					padding_size = avail;
				fast_memset(out->str + out->str_l, ' ', padding_size);
			}
			out->str_l += n;
		}
	}
}
