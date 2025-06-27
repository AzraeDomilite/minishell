/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_padding.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:22:44 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 19:22:52 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

void	handle_left_padding(t_format_info *info, t_arg_data *arg, \
						t_output_buffer *out)
{
	int		n;
	size_t	avail;
	size_t	padding_size;
	char	padding_char;

	if (!info->justify_left)
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
				if (info->zero_padding)
					padding_char = '0';
				else
					padding_char = ' ';
				fast_memset(out->str + out->str_l, padding_char, padding_size);
			}
			out->str_l += n;
		}
	}
}

void	handle_zero_padding_prefix(t_arg_data *arg, t_output_buffer *out)
{
	int		n;
	size_t	avail;
	size_t	copy_size;

	n = arg->zero_padding_insertion_ind;
	if (n > 0)
	{
		if (out->str_l < out->str_m)
		{
			avail = out->str_m - out->str_l;
			copy_size = (size_t)n;
			if (copy_size > avail)
				copy_size = avail;
			fast_memcpy(out->str + out->str_l, arg->str_arg, copy_size);
		}
		out->str_l += n;
	}
}

void	handle_zero_padding_zeros(t_arg_data *arg, t_output_buffer *out)
{
	int		n;
	size_t	avail;
	size_t	copy_size;

	n = arg->zeros_to_pad;
	if (n > 0)
	{
		if (out->str_l < out->str_m)
		{
			avail = out->str_m - out->str_l;
			copy_size = (size_t)n;
			if (copy_size > avail)
				copy_size = avail;
			fast_memset(out->str + out->str_l, '0', copy_size);
		}
		out->str_l += n;
	}
}

void	handle_zero_padding(t_arg_data *arg, t_output_buffer *out)
{
	if (arg->zeros_to_pad <= 0)
	{
		arg->zero_padding_insertion_ind = 0;
	}
	else
	{
		handle_zero_padding_prefix(arg, out);
		handle_zero_padding_zeros(arg, out);
	}
}

void	insert_formatted_string(t_arg_data *arg, t_output_buffer *out)
{
	int		n;
	size_t	avail;
	size_t	copy_size;

	n = arg->str_arg_l - arg->zero_padding_insertion_ind;
	if (n > 0)
	{
		if (out->str_l < out->str_m)
		{
			avail = out->str_m - out->str_l;
			copy_size = (size_t)n;
			if (copy_size > avail)
				copy_size = avail;
			fast_memcpy(out->str + out->str_l,
				arg->str_arg + arg->zero_padding_insertion_ind, \
					copy_size);
		}
		out->str_l += n;
	}
}
