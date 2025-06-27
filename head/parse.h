/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:48:06 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 19:43:23 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "shell.h"
# include "cmd.h"
# include "tokens.h"

t_ntype		ntype_from_operator(char *op);
t_tokens	*tokens_lstsub(t_tokens *left, t_tokens *right);
t_tokens	*tokens_find_outside_brackets(t_tokens *start, char *needles[]);
t_mods		*parse_mod_tokens(t_tokens **tokens_before);
t_mods		*parse_mods(t_tokens **tokens_before);
t_ctree		*parse_tree(t_tokens *tokens);
void		reduce_tree(t_ctree **node);
t_tokens	*tokens_last(t_tokens *somewhere);

#endif