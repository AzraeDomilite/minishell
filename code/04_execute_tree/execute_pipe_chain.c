/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_chain.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:26:37 by baschnit          #+#    #+#             */
/*   Updated: 2025/02/14 15:26:07 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "debug.h"
#include "libft.h"
#include "shell.h"
#include "tree.h"
#include "execute.h"

pid_t	pipe_tree(t_ctree *tree, int fd_in, int fd_out, t_shell *shell)
{
	pid_t	pid;
	t_pipe	*ppipe;

	printf_debug("pipe tree\n");
	ppipe = add_new_pipe(&(shell->pipes));
	if (tree->right->node->type == SUBSHELL)
		pid = fork_tree_no_wait(tree->right->left, (int [2]){ppipe->read, \
		fd_out}, shell, tree->right->node->mods);
	else
		pid = fork_tree_no_wait(tree->right, (int [2]){ppipe->read, fd_out}, \
		shell, NULL);
	close(ppipe->read);
	printf_debug("right side of pipe started\n");
	if (tree->left->node->type == SUBSHELL)
		fork_tree(tree->left->left, (int [2]){fd_in, ppipe->write}, \
		shell, tree->left->node->mods);
	else
		fork_tree(tree->left, (int [2]){fd_in, ppipe->write}, shell, NULL);
	close(ppipe->write);
	ft_lstremove((t_list *) ppipe, (t_list **) &(shell->pipes), free);
	print_debug("pipe closed");
	return (pid);
}

pid_t	chain_tree(t_ctree *tree, int fd_in, int fd_out, t_shell *shell)
{
	shell->ret_last_cmd = execute_tree(tree->left, fd_in, fd_out, shell);
	if (tree->node->type == CHAIN_ON_SUCCESS && !shell->ret_last_cmd)
		return (execute_tree_no_wait(tree->right, fd_in, fd_out, shell));
	else if (tree->node->type == CHAIN_ON_FAIL && shell->ret_last_cmd)
		return (execute_tree_no_wait(tree->right, fd_in, fd_out, shell));
	else if (tree->node->type == CHAIN && tree->right)
		return (execute_tree_no_wait(tree->right, fd_in, fd_out, shell));
	return (-1);
}
