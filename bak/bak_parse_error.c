/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:08:34 by baschnit          #+#    #+#             */
/*   Updated: 2024/12/25 19:08:34 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_error.h"

void	parse_error_handler(t_parse_errno new_error, char *new_arg, t_parse_errno *get_error, char **get_arg)
{
	static t_parse_errno	error;
	static char				*arg;

	if (get_error && get_arg)
		*get_error = error;
	else if (get_arg)
		*get_arg = arg;
	else if (!new_error)
	{
		if (arg)
			free(arg);
	}
	else
	{
		if (!set(arg, ft_strdup(new_arg)))
			error = 0;
		else
			error = new_error;
	}
}

t_parse_errno	errno_parse(void)
{
	t_parse_errno	errno;

	parse_error_handler(0, 0, &errno, 0);
	return (errno);
}

char	*errstr_parse(void)
{
	char	*errstr;

	parse_error_handler(0, 0, 0, &errstr);
	return (errstr);
}

void	set_parse_error(int errno, char *errstr)
{
	parse_error_handler(errno, errstr, 0, 0);
}

void	free_parse_errstr(void)
{
	parse_error_handler(0, 0, 0, 0);
}
