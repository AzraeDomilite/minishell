/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:18:57 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 19:10:52 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include "lines.h"
# include "shell.h"
# include "tokens.h"

/**
 * @brief
 *
*/
typedef enum e_open
{
	NO_ERROR,
	OPEN_SINGLE_QUOTE,
	OPEN_DOUBLE_QUOTE,
	LAST_BACK_SLASH,
	CLOSED_ROUND_BRACKET,
	OPEN_ROUND_BRACKET
}	t_open;

char	*readline_fork(const char *prompt, t_shell *shell, char *heredoc_eof, \
	char *heredoc_free[2]);
char	*read_next_line(t_shell *shell, int first_line, char *heredoc_eof, \
	char *heredoc_free[2]);
int		read_here_docs(t_tokens *tokens, char **history_ref, t_shell *shell);
char	*read_lines(t_tokens **return_tokens, char **here_doc_history, \
		t_shell *shell);

char	*read_heredoc_file(t_shell *shell);
pid_t	child_heredoc(char *eof);

#endif