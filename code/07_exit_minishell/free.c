/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:51:03 by blucken           #+#    #+#             */
/*   Updated: 2025/04/06 11:19:32 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "cmd.h"
#include "tree.h"
#include "libft.h"
#include "tokens.h"
#include "free.h"

int	close_non_std_fd(int fd)
{
	if (fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
		return (close(fd));
	return (0);
}

void	ft_treeclear(t_tree **tree, void (*del)(void*))
{
	if (!*tree)
		return ;
	ft_treeclear(&((*tree)->left), del);
	ft_treeclear(&((*tree)->right), del);
	del((*tree)->content);
	free((*tree));
	*tree = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd->name);
	ft_lstclear((t_list **) &(cmd->args), free);
	free(cmd);
}

void	free_node(t_node *node)
{
	if (node->cmd)
		free_cmd(node->cmd);
	free_mods(&node->mods);
	free(node);
}

void	free_ctree(t_ctree **tree)
{
	ft_treeclear((t_tree **) tree, (void (*)(void *)) free_node);
}
