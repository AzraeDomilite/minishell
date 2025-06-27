/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_tokens_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:23:59 by blucken           #+#    #+#             */
/*   Updated: 2025/03/03 14:24:02 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tokens.h"
#include "tree.h"

/**
 * @brief return type code by checking the supplied string
 *
 * The function will return a type code respective to the operator found on the
 * start of the c string op.
 *
 * @param op c string which holds an operator at the start
 * @return t_ntype type code respective to the operator found
*/
t_ntype	ntype_from_operator(char *op)
{
	if (!op)
		return (COMMAND);
	else if (!ft_strncmp(op, "&&", 2))
		return (CHAIN_ON_SUCCESS);
	else if (!ft_strncmp(op, "||", 2))
		return (CHAIN_ON_FAIL);
	else if (!ft_strncmp(op, ";", 1))
		return (CHAIN);
	else if (!ft_strncmp(op, "|", 1))
		return (PIPE);
	return (0);
}

t_tokens	*tokens_lstsub(t_tokens *left, t_tokens *right)
{
	return ((t_tokens *) ft_lstsub((t_list *) left, (t_list *) right, \
	(void *)(void *)ft_strdup, free));
}

t_tokens	*tokens_find_outside_brackets(t_tokens *start, char *needles[])
{
	char	**begin;
	int		brackets;

	brackets = 0;
	while (start)
	{
		begin = needles;
		if (!ft_strcmp(start->token, ")"))
			brackets--;
		while (!brackets && *begin)
		{
			if (!ft_strcmp(start->token, *begin))
				return (start);
			begin++;
		}
		if (!ft_strcmp(start->token, "("))
			brackets++;
		start = start->next;
	}
	return (NULL);
}
