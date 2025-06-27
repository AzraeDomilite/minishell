/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:25:24 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 17:32:05 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "shell.h"
#include "tokens.h"
#include "read.h"
#include "debug.h"
#include "error.h"
#include "execute.h"

/**
 * @file	read_heredocs.c @brief	filling there heredocs for a tokenized
 * 			command
 *
 * after a user has entered a complete command, the command will be scanned for
 * heredocs ("<< heredoc_end_marker"). Each of these heredocs will then be
*/

/**
 * @brief		gets the next line from the buffer or readline if buffer is
 * 				empty
 *
 * If STDIN is a terminal, the function will ask the user for a next line in case
 * the buffer is empty.
 *
 * If STDIN is not a terminal, the function will return the output of
 * get_next_line.
 *
 * @param shell	global shell structure
 * @return		returns the next line from buffer or user input
*/
char	*next_line_heredoc(t_shell *shell, char *eof, char *buff, char *history)
{
	char	*new;
	char	*temp;

	if (isatty(STDIN_FILENO))
	{
		new = read_next_line(shell, 0, eof, (char *[]){buff, history});
		if (!new)
			return (NULL);
		temp = new;
		new = ft_strjoin(new, "\n");
		free(temp);
	}
	else
	{
		new = get_next_line(STDIN_FILENO);
		if (!new)
		{
			ft_cancel_newline_at_end(eof);
			ft_eprintf(EMSG_HEREDOC_DELIM_BY_EOF, SHELL_NAME, eof);
			shell->continue_loop = 0;
			return (ft_strdup(eof));
		}
	}
	return (new);
}

/**
 * @brief		read the next heredoc
 *
 * Reads the next heredoc until the heredoc marker eof.
 *
 * @param eof	string of heredoc end marker
 * @param shell	global shell structure
 * @return		returns the content of the heredoc in case of success
*/
char	*read_heredoc(char *eof, t_shell *shell, char *heredoc_history)
{
	char	*temp;
	char	*new;
	char	*buff;

	new = ft_strdup("");
	buff = ft_strdup("");
	eof = ft_strjoin(eof, "\n");
	while (ft_strcmp(eof, new))
	{
		free(new);
		if (!set(&new, next_line_heredoc(shell, eof, buff, heredoc_history)))
			return (free(buff), free(eof), NULL);
		if (!ft_strcmp(eof, new))
			break ;
		temp = buff;
		buff = ft_strjoin(buff, new);
		free(temp);
	}
	free(new);
	buff = expand_var_heredoc(eof, buff, shell);
	free(eof);
	return (buff);
}

void	append_heredoc_to_history(char **history, char *temp, t_tokens *tokens)
{
	char	*temp2;

	temp2 = *history;
	*history = ft_strjoin(*history, temp);
	free(temp2);
	temp2 = ft_strjoin(*history, tokens->token);
	free(*history);
	*history = ft_strjoin(temp2, "\n");
	free(temp2);
}

/**
 * @brief				will go through a tokenized shell command and will read
 * 						in each heredoc in the command
 *
 * For each heredoc operator in the tokens a new heredoc will be read and saved
 * to the respective token instead of the original heredoc end marker.
 *
 * At the same time the history will be updated with the inserted heredocs.
 *
 * @param tokens		tokenized shell command to be scanned for heredocs
 * @param history_ref	char array of shell history
 * @param shell			global shell structure
 * @return				returns 1 in case of success
*/
int	read_here_docs(t_tokens *tokens, char **history_ref, t_shell *shell)
{
	char	*temp;
	char	*history;

	history = ft_strdup("");
	while (tokens)
	{
		if (!ft_strcmp(tokens->token, "<<"))
		{
			tokens = tokens->next;
			temp = read_heredoc(tokens->token, shell, history);
			if (!temp)
				return (free(history), 0);
			append_heredoc_to_history(&history, temp, tokens);
			free(tokens->token);
			tokens->token = temp;
		}
		tokens = tokens->next;
	}
	*history_ref = history;
	return (1);
}
