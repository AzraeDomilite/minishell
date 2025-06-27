/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:23:13 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 19:44:21 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tree.h"
#include "tokens.h"

/**
 * @brief			returns the last item in a list of tokens
 *
 * @param somewhere	some point in a linked list of tokens
 * @return			t_tokens*	last element of the linked list
*/
t_tokens	*tokens_last(t_tokens *somewhere)
{
	return ((t_tokens *) ft_lstlast((t_list *) somewhere));
}

void	add_mod_to_pipe(t_ctree *target, t_mods *mods, int in_or_out)
{
	if (target->node->type != PIPE)
	{
		ft_lstadd_front((t_list **) &(target->node->mods), (t_list *) mods);
	}
	else
	{
		if (in_or_out)
			add_mod_to_pipe(target->left, mods, in_or_out);
		else
			add_mod_to_pipe(target->right, mods, in_or_out);
	}
}

void	add_mods_to_pipe(t_mods *mods, t_ctree *left, t_ctree *right)
{
	t_mods	*first_in;
	t_mods	*first_out;
	t_mods	*previous;

	first_in = NULL;
	first_out = NULL;
	while (mods)
	{
		previous = mods;
		mods = mods->next;
		previous->next = NULL;
		if (previous->mod->type == INFILE || previous->mod->type == HEREDOC)
			ft_lstadd_back((t_list **) &first_in, (t_list *) previous);
		else
			ft_lstadd_back((t_list **) &first_out, (t_list *) previous);
	}
	add_mod_to_pipe(left, first_in, 1);
	add_mod_to_pipe(right, first_out, 0);
}

void	reduce_tree(t_ctree **node);

int	reduce_if_subshell(t_ctree *tree)
{
	if (tree->node->type != SUBSHELL)
	{
		reduce_tree(&(tree->left));
		reduce_tree(&(tree->right));
		return (1);
	}
	return (0);
}

/**
 * @brief will remove unnecessary subshells in the execution tree
 *
 * When parsing the execution tree of a command line, several subshells in a row
 *  or a subshell in a pipe would be superfluous. E.g. "(((ls)))" will be
 * effectively the same as "ls" and "(ls) | cat" is the same as "ls | cat",
 * because pipes will always spawn in a forked process.
 *
 * In case of a removal of subshells that have modifiers, the modifiers will be
 * conserved and added to the highest level subshell or the parent pipe.
 *
 * Only a subshell which holds an operator as its child node will be conserved.
 *
 * The subshell will be removed by setting the parent anchor of the subshell
 * node to the subshell nodes child node and freeing the subshell node.
 *
 * @param node	pointer to the anchor (left or right) of a parent node
*/
void	reduce_tree(t_ctree **node)
{
	t_ctree	*tree;

	tree = *node;
	if (!tree)
		return ;
	if (reduce_if_subshell(tree))
		return ;
	if (tree->left->node->type == COMMAND || tree->left->node->type == SUBSHELL \
	|| tree->left->node->type == PIPE)
	{
		*node = tree->left;
		if (tree->left->node->type == PIPE)
			add_mods_to_pipe(tree->node->mods, tree->left->left, \
			tree->left->right);
		else
			ft_lstadd_front((t_list **) &(tree->left->node->mods), \
			(t_list *) tree->node->mods);
		free(tree->node);
		free(tree);
		reduce_tree(node);
	}
	else
		reduce_tree(&(tree->left));
}
