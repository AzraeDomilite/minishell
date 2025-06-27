/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:49:40 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:51:11 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SNPRINTF_H
# define FT_SNPRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <sys/types.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include <errno.h>
# define BREAKEVEN_POINT 6

typedef struct s_format_info
{
	size_t	min_field_width;
	size_t	precision;
	int		zero_padding;
	int		precision_specified;
	int		justify_left;
	int		alternate_form;
	int		force_sign;
	int		space_for_positive;
	char	length_modifier;
	char	fmt_spec;
}	t_format_info;

typedef struct s_output_buffer
{
	char	*str;
	size_t	str_m;
	size_t	str_l;
}	t_output_buffer;

typedef struct s_arg_data
{
	const char	*str_arg;
	size_t		str_arg_l;
	size_t		zeros_to_pad;
	size_t		zero_padding_insertion_ind;
}	t_arg_data;

union u_value
{
	int						ival;
	unsigned int			uival;
	long int				lval;
	unsigned long int		ulval;
	void					*pval;
	long long int			llval;
	unsigned long long int	ullval;
};

/**
 * @brief Format and print data to a string with size limit
 *
 * This function formats and stores a series of characters and values
 * in the buffer str. The function works like sprintf, but ensures the
 * output doesn't exceed size bytes (including null terminator).
 *
 * @param str    Pointer to the buffer where the result is stored
 * @param size   Maximum number of bytes to be written (including null byte)
 * @param format Format string containing text and format specifiers
 * @param ...    Arguments to be formatted according to format specifiers
 *
 * @return The number of characters that would have been written if size had been
 *         sufficiently large, not counting the terminating null character
 */
int		ft_snprintf(char *str, size_t size, const char *format, ...);

/**
 * @brief Format and print data to a string with size limit using va_list
 *
 * This function is equivalent to ft_snprintf, except that it accepts
 * a va_list parameter instead of variable arguments.
 *
 * @param str    Pointer to the buffer where the result is stored
 * @param str_m  Maximum number of bytes to be written (including null byte)
 * @param fmt    Format string containing text and format specifiers
 * @param ap     List of arguments to be formatted according to format 
 * 				 specifiers
 *
 * @return The number of characters that would have been written if str_m 
 * 		   had been sufficiently large, not counting the terminating 
 * 		   null character
 */
int		ft_vsnprintf(char *str, size_t str_m, const char *fmt, va_list ap);

/* Format info functions */
void	init_format_info(t_format_info *info);
void	parse_flags(t_format_info *info, const char **p);
void	parse_field_width(t_format_info *info, const char **p, va_list ap);
void	parse_precision(t_format_info *info, const char **p, va_list ap);
void	handle_flag(t_format_info *info, char flag);

/* Format parsing functions */
void	parse_length_modifier(t_format_info *info, const char **p);
void	handle_format_synonym(t_format_info *info, char spec);
void	handle_char_string_format(t_format_info *info, t_arg_data *arg, \
			va_list ap);
void	handle_unknown_format(t_format_info *info, t_arg_data *arg, \
			const char **p);

/* String precision functions*/
void	handle_string_precision(t_format_info *info, t_arg_data *arg);

/* Numeric setup functions */
void	set_numeric_arg_pointer(t_format_info *info, union u_value *value, \
			int *arg_sign, va_list ap);
void	set_numeric_arg_signed(t_format_info *info, union u_value *value, \
			int *arg_sign, va_list ap);
void	set_numeric_arg_unsigned(t_format_info *info, union u_value *value, \
			int *arg_sign, va_list ap);
void	handle_sign_and_alt_form(t_format_info *info, t_arg_data *arg, \
			int arg_sign, char *tmp);
void	handle_special_padding_cases(t_arg_data *arg, char *tmp);

/* Numeric format functions */
int		format_numeric_arg(t_format_info *info, char *tmp, size_t *str_arg_l, \
			void *arg_value);
void	format_numeric_value(t_format_info *info, t_arg_data *arg, \
			union u_value *value, char *tmp);
void	calculate_padding(t_format_info *info, t_arg_data *arg, char *tmp);
int		handle_numeric_format(t_format_info *info, t_arg_data *arg, \
			va_list ap, char *tmp);
void	handle_right_padding(t_format_info *info, t_arg_data *arg, \
			t_output_buffer *out);

/* Padding functions */
void	handle_left_padding(t_format_info *info, t_arg_data *arg, \
			t_output_buffer *out);
void	handle_zero_padding_prefix(t_arg_data *arg, t_output_buffer *out);
void	handle_zero_padding_zeros(t_arg_data *arg, t_output_buffer *out);
void	handle_zero_padding(t_arg_data *arg, t_output_buffer *out);
void	insert_formatted_string(t_arg_data *arg, t_output_buffer *out);

/* Core functions */
void	process_non_format_chars(t_output_buffer *out, const char **p);
void	prepare_format_info(t_format_info *info, t_arg_data *arg, \
			const char **p, va_list ap);
void	process_format_specifier(t_output_buffer *out, \
			const char **p, va_list ap);

/* Utility functions */
void	fast_memset(void *d, int c, size_t n);
void	fast_memcpy(void *d, const void *s, size_t n);
size_t	ft_numlen_base(unsigned long n, int base);
size_t	ft_itoa_to_buf(int n, char *buf);
size_t	ft_utoa_to_buf(unsigned int n, char *buf);
size_t	ft_itoa_base_to_buf(unsigned long value, char *buf, \
			int base, int uppercase);

# ifndef LIBFT
#  define LIBFT

int		isdigit(int c);
char	*ft_utoa(unsigned int n);
char	*ft_itoa_base(int value, int base);
char	*ft_itoa(int n);
# endif

#endif
