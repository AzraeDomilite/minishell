/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:20:38 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 18:53:44 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

#include "shell.h"
#include "libft.h"
#include "cmd.h"
#include "child.h"
#include "tree.h"
#include "execute.h"
#include "debug.h"
#include "builtins.h"
#include "free.h"

pid_t	execute_tree_no_wait(t_ctree *tree, int fd_in, \
int fd_out, t_shell *shell)
{
	pid_t	pid;

	if (tree->node->type == COMMAND)
	{
		pid = execute_cmd(tree->node, fd_in, fd_out, shell);
		printf_debug("errno %i\n", errno);
		printf_debug("cmd_executed from execute_tree_no_wait, pid = %i\n", pid);
	}
	else if (tree->node->type == SUBSHELL)
	{
		pid = fork_tree_no_wait(tree->left, (int [2]){fd_in, fd_out}, \
		shell, tree->node->mods);
	}
	else if (tree->node->type == PIPE)
		pid = pipe_tree(tree, fd_in, fd_out, shell);
	else
		pid = chain_tree(tree, fd_in, fd_out, shell);
	return (pid);
}

int	execute_tree(t_ctree *tree, int fd_in, int fd_out, t_shell *shell)
{
	pid_t	pid;
	int		wstatus;

	wstatus = 0;
	printf_debug("execute tree\n");
	pid = execute_tree_no_wait(tree, fd_in, fd_out, shell);
	if (tree->node->type == COMMAND && \
		builtin_change_sh_state(tree->node->cmd->name))
		return (pid);
	if (pid != -1)
		waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		printf_debug("exit status %i\n", WEXITSTATUS(wstatus));
		return (WEXITSTATUS(wstatus));
	}
	else
		return (-1);
}

pid_t	fork_tree_no_wait(t_ctree *tree, int fd[2], t_shell *shell, \
	t_mods *mods)
{
	pid_t	pid;
	int		ret;
	int		fd_in;
	int		fd_out;

	fd_in = fd[0];
	fd_out = fd[1];
	if (tree->node->type == COMMAND)
		return (execute_cmd(tree->node, fd_in, fd_out, shell));
	printf_debug("fork no wait with fd_in %i, fd_out %i and fd_close\n", \
	fd_in, fd_out);
	pid = fork();
	if (!pid)
	{
		apply_modifiers(mods, &fd_in, &fd_out);
		close_all_pipes_except(fd_in, fd_out, shell->pipes);
		ret = execute_tree(tree, fd_in, fd_out, shell);
		close_non_std_fd(fd_in);
		close_non_std_fd(fd_out);
		free_shell(shell);
		exit((int) ret);
	}
	return (pid);
}

int	fork_tree(t_ctree *tree, int fd[2], t_shell *shell, t_mods *mods)
{
	pid_t	pid;
	int		wstatus;

	printf_debug("fork wait\n");
	pid = fork_tree_no_wait(tree, fd, shell, mods);
	if (pid != -1)
		waitpid(pid, &wstatus, 0);
	if WIFEXITED(wstatus)
		return (WEXITSTATUS(wstatus));
	else
		return (-1);
}
