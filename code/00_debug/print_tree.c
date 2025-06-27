/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:06:56 by blucken           #+#    #+#             */
/*   Updated: 2025/03/05 19:06:57 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "cmd.h"
#include "tree.h"
#include "debug.h"
#include "tokens.h"
#include "print_tree.h"

#define INDENT_WIDTH 4

char	*extract_mod(t_mtype type)
{
	if (type == INFILE)
		return (ft_strdup("< "));
	else if (type == OUTFILE)
		return (ft_strdup("> "));
	else if (type == HEREDOC)
		return (ft_strdup("<< "));
	else if (type == OUTFILE_APPEND)
		return (ft_strdup(">> "));
	else
		return (NULL);
}

char	*extract_mods(t_mods *mods)
{
	char	*temp;
	char	*temp2;
	char	*temp3;

	if (!mods)
		return (NULL);
	temp = ft_strdup("");
	while (mods)
	{
		temp3 = extract_mod(mods->mod->type);
		temp2 = temp;
		temp = ft_strjoin(temp, temp3);
		free(temp2);
		free(temp3);
		temp2 = temp;
		temp = ft_strjoin(temp, mods->mod->arg);
		free(temp2);
		temp2 = temp;
		temp = ft_strjoin(temp, " ");
		free(temp2);
		mods = mods->next;
	}
	return (temp);
}

char	*extract_name_and_args(char *name, t_args *args)
{
	char	*temp;
	char	*temp2;

	if (!name)
		return (ft_strdup(""));
	if (!args)
		return (ft_strdup(name));
	temp = ft_strjoin(name, ": |");
	while (args)
	{
		temp2 = temp;
		temp = ft_strjoin(temp, args->arg);
		free(temp2);
		temp2 = temp;
		temp = ft_strjoin(temp, "|");
		free(temp2);
		args = args->next;
	}
	return (temp);
}

char	*extract_node_type(t_ntype type)
{
	if (type == PIPE)
		return (ft_strdup("|"));
	else if (type == CHAIN)
		return (ft_strdup(";"));
	else if (type == CHAIN_ON_FAIL)
		return (ft_strdup("||"));
	else if (type == CHAIN_ON_SUCCESS)
		return (ft_strdup("&&"));
	else if (type == SUBSHELL)
		return (ft_strdup("FORK"));
	return (NULL);
}

char	*extract_node(t_node *node)
{
	if (node->type == COMMAND)
		return (extract_name_and_args(node->cmd->name, node->cmd->args));
	else
		return (extract_node_type(node->type));
}

void	print_sub_tree_left(t_ctree *tree, int indent, \
	int above_or_below_parent, int fd)
{
	if (tree->node->type != COMMAND && tree->node->type != SUBSHELL)
	{
		print_tree(tree->left, indent + 1, 1);
		dprintf(fd, "%*c/\n", indent * INDENT_WIDTH + INDENT_WIDTH - 1, ' ');
	}
	else if (tree->node->type != COMMAND && above_or_below_parent)
	{
		print_tree(tree->left, indent + 1, 1);
		dprintf(fd, "%*c/\n", indent * INDENT_WIDTH + INDENT_WIDTH - 1, ' ');
	}
}

void	print_sub_tree_right(t_ctree *tree, int indent, \
	int above_or_below_parent, int fd)
{
	if (tree->node->type != COMMAND && tree->node->type != SUBSHELL)
	{
		dprintf(fd, "%*c\\\n", indent * INDENT_WIDTH + INDENT_WIDTH - 1, ' ');
		print_tree(tree->right, indent + 1, 0);
	}
	else if (tree->node->type != COMMAND && !above_or_below_parent)
	{
		dprintf(fd, "%*c\\\n", indent * INDENT_WIDTH + INDENT_WIDTH - 1, ' ');
		print_tree(tree->left, indent + 1, 0);
	}
}

/**
 * @brief recursively prints a shell cmd in tree structure to a debug fd
 *
 * A shell command can be parsed into a tree depending on the pipes or command
 * chains and the resulting execution order. To visualize the resulting hirarchy
 *  this function will recursively print this structure with piping or chaining
 * operators as nodes and single commands as the leafs.
 *
 * @param tree				shell command parsed into a tree structure
 * @param indent 			indentation from the left to print out on each
 * level of the tree
 * @param above_or_below 	saying if the current node will be printed above
 * or below the parent node (left or right in the tree)
*/
void	print_tree(t_ctree *tree, int indent, int above_or_below)
{
	char	*temp;
	char	*mods;
	int		fd;

	fd = get_debug_fd();
	if (!tree)
		return ;
	print_sub_tree_left(tree, indent, above_or_below, fd);
	temp = extract_node(tree->node);
	mods = extract_mods(tree->node->mods);
	if (mods)
		dprintf(fd, "%*c %s %s\n", indent * INDENT_WIDTH, ' ', temp, mods);
	else
		dprintf(fd, "%*c %s\n", indent * INDENT_WIDTH, ' ', temp);
	free(temp);
	if (mods)
		free(mods);
	print_sub_tree_right(tree, indent, above_or_below, fd);
}
