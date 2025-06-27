/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:58:37 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 17:21:09 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdarg.h>

#include "libft.h"
#include "shell.h"
#include "lines.h"
#include "tree.h"
#include "parse.h"
#include "execute.h"
#include "read.h"
#include "free.h"
#include "debug.h"
#include "print_tree.h"
#include "builtins.h"
#include "history.h"
#include "tokens.h"
#include "free.h"

/**
 * @brief	receives a complete command, parses the command into a tree and
 * 			executes it
 *
 * @param cmd_line
 * @param here_docs
 * @param tokens
 * @param shell
*/
static void	parse_and_execute_command(char **cmd_line, char **here_docs, \
t_tokens *tokens, t_shell *shell)
{
	char	*temp;

	temp = *cmd_line;
	set(cmd_line, ft_strjoin(*cmd_line, *here_docs));
	free(*here_docs);
	*here_docs = NULL;
	free(temp);
	if (!manage_history(shell, *cmd_line))
	{
		ft_dprintf(STDERR_FILENO, "could not read readline history");
		free(*cmd_line);
		ft_lstclear((t_list **) &tokens, free);
		free_on_exit(shell, 1);
	}
	free(*cmd_line);
	shell->tree = parse_tree(tokens);
	ft_lstclear((t_list **) &tokens, free);
	shell->ret_last_cmd = execute_tree(shell->tree, \
	STDIN_FILENO, STDOUT_FILENO, shell);
	free_ctree(&(shell->tree));
	free_pipes(&(shell->pipes));
}

/**
 * @brief	loop over every written/pasted line until the last complete
 * 			command
 *
 * - read_lines will read a complete command - process command will parse and
 * execute this command - if shell->buffer_line is not NULL that means there are
 * still lines in the buffer - the loop will continue until the buffer is empty
 * and the last command is complete (if a command is incomplete read_lines will
 * execute readline to ask for more user input)
 *
*/
int	read_and_execute_command(t_shell *shell, char **here_docs, int *first_run)
{
	char		*cmd_line;
	t_tokens	*tokens;

	while (*first_run || \
	(shell->stdin_tty && shell->buffer_line && *shell->buffer_line))
	{
		print_debug("starting handle command line");
		*first_run = 0;
		if (!set(&cmd_line, read_lines(&tokens, here_docs, shell)))
			return (0);
		if (cmd_line && ft_strcmp(cmd_line, ""))
			parse_and_execute_command(&cmd_line, here_docs, tokens, shell);
		else
		{
			free(*here_docs);
			*here_docs = NULL;
		}
	}
	return (1);
}

/**
 * @brief		will loop to get a full command until shell->continue_loop is
 * 				0
 *
 * This loop will rerun after one complete command has been read and executed
 * via read_and_execute_command()
 *
 * @param shell	central shell structure
*/
void	minishell_loop(t_shell *shell)
{
	char	*history;
	int		first_run;

	history = NULL;
	while (shell->continue_loop)
	{
		first_run = 1;
		read_and_execute_command(shell, &history, &first_run);
		if (shell->buffer)
			free_buffer(shell);
	}
}
