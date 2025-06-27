/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:39:59 by blucken           #+#    #+#             */
/*   Updated: 2024/12/12 12:19:19 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_TREE_H
# define PRINT_TREE_H

# include <stdio.h>
# include <stddef.h>

# include "cmd.h"
# include "tree.h"

void	print_tree(t_ctree *tree, int indent, int above_or_below);

#endif