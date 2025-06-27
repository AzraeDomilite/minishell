/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:04:13 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:53:07 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

#include "free.h"
#include "debug.h"
#include "libft.h"
#include "shell.h"
#include "tokens.h"
#include "read.h"
#include "check_cmd.h"
#include "signals.h"
#include "execute.h"
#include "error.h"
/**
 * @brief		read next line from buffer or user input
 *
 * bash buffers the user input, when multiple lines are pasted at once.
 * Afterwards, the lines will be executed one by one.
 *
 * This functions mimics this behaviour by buffering multiple lines when pasted
 * into the shell->buffer and returning them one by one, each time a new line is
 * requested. When the buffer is empty, the user will be asked for input via
 * readline once again.
 *
 * @param shell	central data structure
 * @return		char*	next line from buffer or from user input
*/

char	*read_next_line(t_shell *shell, int first_line, char *heredoc_eof, \
	char *heredoc_free[2])
{
	char	*new;

	if (!shell->buffer_line || !*(shell->buffer_line))
	{
		if (shell->buffer)
			free_buffer(shell);
		if (first_line)
			new = "$ ";
		else
			new = "> ";
		new = readline_fork(new, shell, heredoc_eof, heredoc_free);
		if (!new)
			return (NULL);
		shell->buffer = ft_split(new, '\n');
		shell->buffer_line = shell->buffer;
		free(new);
	}
	if (!*(shell->buffer))
		return (ft_strdup(""));
	shell->buffer_line++;
	return (ft_strdup(*(shell->buffer_line - 1)));
}


static char	*find_line_concatenator(char **total, t_tokens *tokens)
{
	char	*new;
	char	*temp;

	if (ft_check_quotes(ft_lstlast((t_list *)tokens)->content))
		return (ft_strdup("\n"));
	if (*ft_strend(*total) == '\\')
	{
		ft_remove_last_backslash(*total);
		return (ft_strdup(""));
	}
	temp = check_completeness(tokens);
	if (temp)
	{
		new = *total;
		*total = ft_strjoin(*total, temp);
		free(new);
	}
	return (temp);
}


static void	cleanup_temp_total(char *temp, char **total, char *new)
{
	*total = ft_strjoin_null(*total, new);
	free(new);
	free(temp);
}

int	read_until_complete(t_shell *shell, char **temp, char **new, int first_line)
{
	if (!shell->stdin_tty)
	{
		if (!set(new, get_next_line(STDIN_FILENO)))
		{
			if (shell->tokens)
				ft_eprintf(EMSG_SYNTAX_UNEXPECTED_EOF, SHELL_NAME);
			return (shell->continue_loop = 0, free(shell->total), 0);
		}
		ft_cancel_newline_at_end(*new);
	}
	else if (!set(new, read_next_line(shell, first_line, NULL, \
		(char *[]){NULL, NULL})))
		return (free(shell->total), 0);
	*temp = shell->total;
	cleanup_temp_total(*temp, &shell->total, *new);
	if (!set(&shell->tokens, tokenize_cmd(shell->total)))
		return (free(shell->total), 0);
	if (!check_syntax(shell->tokens))
	{
		shell->ret_last_cmd = 2;
		if (!shell->stdin_tty)
			shell->continue_loop = 0;
		return (free(shell->total), free_tokens(&shell->tokens), 0);
	}
	return (1);
}

/**
 * @brief	read from buffer or user input until a complete command results
 *
 * As long as command is not complete, check_syntax_and_completeness will return
 * a non-NULL separator into temp.
 *
 * @param return_tokens
 * @param here_doc_history
 * @param shell
 * @return	char*
*/
char	*read_lines(t_tokens **return_tokens, char **here_doc_history, \
t_shell *shell)
{
	char	*temp;
	char	*new;
	int		first_line;

	first_line = 1;
	temp = ft_strdup("");
	shell->total = ft_strdup("");
	shell->tokens = NULL;
	while (temp)
	{
		free(temp);
		if (!read_until_complete(shell, &temp, &new, first_line))
			return (NULL);
		first_line = 0;
		temp = find_line_concatenator(&shell->total, shell->tokens);
	}
	print_debug("printing tokens");
	print_tokens(shell->tokens);
	if (!read_here_docs(shell->tokens, here_doc_history, shell))
		return (ft_lstclear((t_list **) &shell->tokens, free), \
		free(shell->total), NULL);
	*return_tokens = shell->tokens;
	ft_cancel_newline_at_end(shell->total);
	return (shell->total);
}
