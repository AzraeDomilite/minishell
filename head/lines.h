/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:17:09 by baschnit          #+#    #+#             */
/*   Updated: 2025/02/10 15:16:11 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINES_H
# define LINES_H

/**
 * @brief holds a list of the lines
 *
*/
typedef struct s_lines
{
	char			*line;
	struct s_lines	*next;
}	t_lines;

#endif