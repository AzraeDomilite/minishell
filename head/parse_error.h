/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 19:09:21 by baschnit          #+#    #+#             */
/*   Updated: 2025/02/14 12:07:06 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ERROR_H
# define PARSE_ERROR_H

typedef enum e_parse_errno
{
	UNDEFINED_ERROR,
	SYNTAX_ERROR,
}	t_parse_errno;

int		errno_parse(void);
char	errchar_parse(void);
void	set_parse_error(int errno, char errchar);

#endif