/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_only_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 02:40:21 by baschnit          #+#    #+#             */
/*   Updated: 2024/12/07 02:47:40 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief test if string is empty or has only spaces
 *
 * @param test str to analyse
 * @return int 1 if only spaces or empty, 0 if other characters
*/
int	ft_str_only_spaces(const char *test)
{
	while (ft_isspace(*test))
		test++;
	if (*test)
		return (0);
	else
		return (1);
}
