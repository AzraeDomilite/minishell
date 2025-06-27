/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_format_numeric_arg.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:22:56 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 19:23:05 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_snprintf.h"

static int	format_numeric_arg_pointer(t_format_info *info, \
		char *tmp, size_t *str_arg_l, void *arg_value)
{
	size_t	len;

	(void)info;
	tmp[(*str_arg_l)++] = '0';
	tmp[(*str_arg_l)++] = 'x';
	len = ft_itoa_base_to_buf((unsigned long)arg_value, \
		tmp + *str_arg_l, 16, 0);
	*str_arg_l += len;
	return (0);
}

static int	format_numeric_arg_signed(t_format_info *info, char *tmp, \
		size_t *str_arg_l, void *arg_value)
{
	size_t	len;

	if (info->length_modifier == '\0' || info->length_modifier == 'h')
		len = ft_itoa_to_buf(*(int *)arg_value, tmp + *str_arg_l);
	else if (info->length_modifier == 'l')
		len = ft_itoa_to_buf(*(long int *)arg_value, tmp + *str_arg_l);
	else
		len = ft_itoa_to_buf(*(long long int *)arg_value, tmp + *str_arg_l);
	*str_arg_l += len;
	return (0);
}

static int	format_numeric_arg_hex(t_format_info *info, char *tmp, \
		size_t *str_arg_l, void *arg_value)
{
	size_t	len;

	if (info->length_modifier == '\0' || info->length_modifier == 'h')
		len = ft_itoa_base_to_buf(*(unsigned int *)arg_value, \
			tmp + *str_arg_l, 16, info->fmt_spec == 'X');
	else if (info->length_modifier == 'l')
		len = ft_itoa_base_to_buf(*(unsigned long int *)arg_value, \
			tmp + *str_arg_l, 16, info->fmt_spec == 'X');
	else
		len = ft_itoa_base_to_buf(*(unsigned long long int *)arg_value, \
			tmp + *str_arg_l, 16, info->fmt_spec == 'X');
	*str_arg_l += len;
	return (0);
}

static int	format_numeric_arg_unsigned(t_format_info *info, char *tmp, \
		size_t *str_arg_l, void *arg_value)
{
	size_t	len;

	if (info->length_modifier == '\0' || info->length_modifier == 'h')
		len = ft_utoa_to_buf(*(unsigned int *)arg_value, tmp + *str_arg_l);
	else if (info->length_modifier == 'l')
		len = ft_utoa_to_buf(*(unsigned long int *)arg_value, tmp + *str_arg_l);
	else
		len = ft_utoa_to_buf(*(unsigned long long int *)arg_value, \
			tmp + *str_arg_l);
	*str_arg_l += len;
	return (0);
}

int	format_numeric_arg(t_format_info *info, char *tmp, \
		size_t *str_arg_l, void *arg_value)
{
	if (info->fmt_spec == 'p')
		return (format_numeric_arg_pointer(info, tmp, str_arg_l, arg_value));
	else if (info->fmt_spec == 'd')
		return (format_numeric_arg_signed(info, tmp, str_arg_l, arg_value));
	else if (info->fmt_spec == 'x' || info->fmt_spec == 'X')
		return (format_numeric_arg_hex(info, tmp, str_arg_l, arg_value));
	else
		return (format_numeric_arg_unsigned(info, tmp, str_arg_l, arg_value));
}
