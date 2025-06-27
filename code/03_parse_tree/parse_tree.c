/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:24:21 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 19:44:31 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tokens.h"
#include "shell.h"
#include "tree.h"
#include "parse_error.h"
#include "parse.h"

/**
 * @brief			looks for 5 control operator one after another and
 * 					returns as soon as the first is found
 *
 * This function will search the control operators &&, ||, ; or | in the list of
 * tokens, outside of brackets and quotes, by using the function
 * tokens_find_outside_brackets(). If an operator is found, the char double
 * pointers left and right will be set to a substring left and right
 * respectively of the found control operator.
 *
 * The function will return a type code respective to the operator found or the
 * type code COMMAND if no operator is found.
 *
 * @param cmd_line	c string to search operator in
 * @param left		will be set to substring left of found operator
 * @param right		will be set to substring right of found operator
 * @return			t_ntype will be set to type code of found operator
*/
t_ntype	tokens_split_by_operator(t_tokens *tokens, t_tokens **op, \
t_tokens **left, t_tokens **right)
{
	t_tokens	*res;

	res = tokens_find_outside_brackets(tokens, \
	(char *[2]){";", NULL});
	if (!res)
		res = tokens_find_outside_brackets(tokens, \
		(char *[3]){"&&", "||", NULL});
	if (!res)
		res = tokens_find_outside_brackets(tokens, \
		(char *[2]){"|", NULL});
	if (!res && !ft_strcmp(tokens->token, "("))
		return (SUBSHELL);
	if (!res)
		return (COMMAND);
	*left = tokens_lstsub(tokens, res);
	*right = tokens_lstsub(res->next, NULL);
	*op = res;
	return (ntype_from_operator(res->token));
}

/*
 * @brief allocates and initialises a new command tree node
 *
 * The function will allocate a binary tree leave (t_ctree) and its content
 * (t_node). If successfull, it will initiase both structures.
 *
 * If an allocation fails, the function will return NULL.
 *
 * @return	t_ctree* pointer to the newly allocated command tree structure
 *			or NULL if allocation failed
*/
t_ctree	*new_tree_node(void)
{
	t_node	*node;
	t_ctree	*tree;

	if (!set(&node, malloc(sizeof(t_node))))
		return (NULL);
	if (!set(&tree, malloc(sizeof(t_ctree))))
		return (free(node), NULL);
	node->type = -1;
	node->cmd = NULL;
	node->mods = NULL;
	tree->node = node;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

/**
 * @brief			will create a command structure from a list of tokens
 *
 * Creates a newly allocated structure t_cmd by taking the first token as the
 * command name and every following token as an argument or a modifier of
 * stdin/stdout. Returns NULL in case of allocation failure or the newly created
 * structure.
 *
 * @param tokens	list of tokens reduced to a command, its arguments and
 * 					its modifiers
 * @return			t_cmd*	NULL in case of failure or a pointer to the
 * 					newly created structure
*/
t_cmd	*parse_cmd(t_tokens *tokens)
{
	t_cmd	*lcmd;

	if (!set(&lcmd, malloc(sizeof(t_cmd))))
		return (NULL);
	if (!tokens)
	{
		lcmd->name = NULL;
		lcmd->args = NULL;
	}
	else
	{
		lcmd->name = ft_strdup(tokens->token);
		lcmd->args = (t_args *) tokens_lstsub(tokens->next, NULL);
	}
	return (lcmd);
}

void	fill_new_based_on_type(t_ctree *new, t_tokens *left, \
	t_tokens *right, t_tokens *tokens)
{
	if (new->node->type == SUBSHELL)
	{
		new->node->mods = parse_mods(&tokens);
		left = tokens_lstsub(tokens->next, tokens_last(tokens));
		free_tokens(&tokens);
		new->left = parse_tree(left);
		free_tokens(&left);
	}
	else if (new->node->type == COMMAND)
	{
		new->node->mods = parse_mods(&tokens);
		new->node->cmd = parse_cmd(tokens);
		free_tokens(&tokens);
	}
	else
	{
		new->left = parse_tree(left);
		if (!(new->node->type == CHAIN && !right))
			new->right = parse_tree(right);
		free_tokens(&left);
		free_tokens(&right);
	}
}

/**
 * @brief			parse a complete command line and return a command tree
 *
 * This function will parse a command line in form of a list of tokens
 * recursively, creating a tree structure of the command line (in order of
 * execution of the commands and operators).
 *
 * Three cases are handled:
 *
 * 1) Finding and operator via the function tokens_split_operator, creating a
 * node for that operator, and recursively parsing the tokens left and right of
 * the operator
 *
 * 2) Parsing a subshell/brackets (e.g. in "ls && (ls | cat)"), creating a node
 * for the subshell and recursively parsing the inside of the brackets
 *
 * 3) If neither 1 or 2 apply a command is reached which forms a bottom leaf in
 * the tree
 *
 * The function returns the created tree structure.
 *
 * @param tokens	tokenized command line to parse
 * @return			t_ctree* tree structure resulting from the supplied
 * 					command line
*/
t_ctree	*parse_tree(t_tokens *tokens)
{
	t_tokens	*left;
	t_tokens	*right;
	t_tokens	*op;
	t_ntype		type;
	t_ctree		*new;

	left = NULL;
	right = NULL;
	if (!set(&new, new_tree_node()))
		return (NULL);
	type = tokens_split_by_operator(tokens, &op, &left, &right);
	if (!type)
		return (free(new), NULL);
	new->node->type = type;
	fill_new_based_on_type(new, left, right, tokens);
	return (new);
}
