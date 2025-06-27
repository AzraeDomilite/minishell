/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:24:20 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:56:12 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "cmd.h"
#include "shell.h"
#include "libft.h"
#include "debug.h"
#include "parse_env.h"
#include "free.h"
#include "execute.h"
#include "builtins.h"
#include "signals.h"

static pid_t	exec_builtin(int fd_out, t_node	*node, \
	t_shell *shell, t_builtin *builtin);
static void		execve_cmd(char *cmd_path, char **args_tabs, t_shell *shell);

static void	handle_child_process(t_node *node, int fd_in, int fd_out, \
	t_shell *shell)
{
	char	*cmd_path;
	char	**args_tabs;

	cmd_path = NULL;
	restore_signals();
	//apply_modifiers(node->mods, &fd_in, &fd_out);
	expand_vars(node, shell);
	apply_modifiers(node->mods, &fd_in, &fd_out);
	if (node->cmd->name)
	{
		cmd_path = get_cmd_path(node->cmd->name, shell);
		check_access(node->cmd, cmd_path, shell);
		if (fd_in == -1 || fd_out == -1)
			return (free(cmd_path), \
				close_all_pipes(shell->pipes), free_shell(shell), exit(2));
		if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
			return (close_all_pipes(shell->pipes), \
				dup2_error(cmd_path, shell), (void) NULL);
		close_all_pipes_except(fd_in, fd_out, shell->pipes);
		if (!set(&args_tabs, args_list_to_tab(node->cmd)))
			return (close_all_pipes(shell->pipes), \
				args_tab_error(cmd_path, shell), (void) NULL);	
		execve_cmd(cmd_path, args_tabs, shell);	
	}
	close_all_pipes(shell->pipes);
	if(fd_in == STDIN_FILENO)
		close(fd_in);
	if(fd_out == STDOUT_FILENO || fd_out == STDERR_FILENO)
		close(fd_out);
	exit(0);
}

static	pid_t	handle_builtin_no_pipe(t_node *node, int fd_out, \
	t_shell *shell, t_builtin *builtin)
{
	if (builtin && !shell->pipes && builtin_change_sh_state(node->cmd->name))
		return (apply_modifiers(node->mods, 0, &fd_out), \
		exec_builtin(fd_out, node, shell, builtin));
	return (0);
}

pid_t	execute_cmd(t_node *node, int fd_in, int fd_out, t_shell *shell)
{
	pid_t		pid;
	t_builtin	*builtin;

	builtin = in_builtins(node->cmd->name, shell->builtins);
	pid = handle_builtin_no_pipe(node, fd_out, shell, builtin);
	if (builtin_change_sh_state(node->cmd->name))
		return (pid);
	pid = fork();
	if (pid < 0)
		return (fork_error());
	if (pid == 0)
	{
		printf_debug("... forked execute_cmd ...\n");
		if (builtin)
		{
			expand_vars(node, shell);
			exec_builtin(fd_out, node, shell, builtin);
			ft_exit(NULL, 0, shell);
		}
		else
			handle_child_process(node, fd_in, fd_out, shell);
	}
	return (pid);
}

static pid_t	exec_builtin(int fd_out, t_node	*node, t_shell *shell, \
	t_builtin *builtin)
{
	return (builtin->func(node->cmd->args, fd_out, shell));
}

static void	execve_cmd(char *cmd_path, char **args_tabs, t_shell *shell)
{
	execve(cmd_path, args_tabs, shell->env);
	perror("execve : ");
	free(cmd_path);
	ft_free_splits(args_tabs);
	free_shell(shell);
	exit(EXIT_CMD_NOT_EXECUTABLE);
}
