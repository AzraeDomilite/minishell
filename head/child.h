/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:34:52 by baschnit          #+#    #+#             */
/*   Updated: 2024/12/05 01:11:11 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILD_H
# define CHILD_H

# include "cmd.h"

typedef struct s_cmod
{
	t_mtype	type;
	int		fd;
	char	*doc;
}	t_cmod;

#endif