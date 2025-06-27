/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_numeric_setup.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:31:05 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 15:31:05 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

void	set_numeric_arg_pointer(t_format_info *info, union u_value *value, \
							int *arg_sign, va_list ap)
{
	void	*ptr_arg;

	info->length_modifier = '\0';
	ptr_arg = va_arg(ap, void *);
	if (ptr_arg != NULL)
		*arg_sign = 1;
	value->pval = ptr_arg;
}

void	set_numeric_arg_signed(t_format_info *info, union u_value *value, \
							int *arg_sign, va_list ap)
{
	if (info->length_modifier == '\0' || info->length_modifier == 'h')
	{
		value->ival = va_arg(ap, int);
		if (value->ival > 0)
			*arg_sign = 1;
		else if (value->ival < 0)
			*arg_sign = -1;
	}
	else if (info->length_modifier == 'l')
	{
		value->lval = va_arg(ap, long int);
		if (value->lval > 0)
			*arg_sign = 1;
		else if (value->lval < 0)
			*arg_sign = -1;
	}
	else
	{
		value->llval = va_arg(ap, long long int);
		if (value->llval > 0)
			*arg_sign = 1;
		else if (value->llval < 0)
			*arg_sign = -1;
	}
}

void	set_numeric_arg_unsigned(t_format_info *info, union u_value *value, \
								int *arg_sign, va_list ap)
{
	if (info->length_modifier == '\0' || info->length_modifier == 'h')
	{
		value->uival = va_arg(ap, unsigned int);
		if (value->uival)
			*arg_sign = 1;
	}
	else if (info->length_modifier == 'l')
	{
		value->ulval = va_arg(ap, unsigned long int);
		if (value->ulval)
			*arg_sign = 1;
	}
	else
	{
		value->ullval = va_arg(ap, unsigned long long int);
		if (value->ullval)
			*arg_sign = 1;
	}
}

void	handle_sign_and_alt_form(t_format_info *info, t_arg_data *arg, \
								int arg_sign, char *tmp)
{
	if (info->fmt_spec == 'd')
	{
		if (info->force_sign && arg_sign >= 0)
		{
			if (info->space_for_positive)
				tmp[arg->str_arg_l++] = ' ';
			else
				tmp[arg->str_arg_l++] = '+';
		}
	}
	else if (info->alternate_form)
	{
		if (arg_sign != 0 && (info->fmt_spec == 'x' || info->fmt_spec == 'X'))
		{
			tmp[arg->str_arg_l++] = '0';
			tmp[arg->str_arg_l++] = info->fmt_spec;
		}
	}
	arg->zero_padding_insertion_ind = arg->str_arg_l;
}

void	handle_special_padding_cases(t_arg_data *arg, char *tmp)
{
	if (arg->zero_padding_insertion_ind < arg->str_arg_l && \
		tmp[arg->zero_padding_insertion_ind] == '-')
	{
		arg->zero_padding_insertion_ind++;
	}
	if (arg->zero_padding_insertion_ind + 1 < arg->str_arg_l && \
		tmp[arg->zero_padding_insertion_ind] == '0' && \
		(tmp[arg->zero_padding_insertion_ind + 1] == 'x' || \
		tmp[arg->zero_padding_insertion_ind + 1] == 'X'))
	{
		arg->zero_padding_insertion_ind += 2;
	}
}
