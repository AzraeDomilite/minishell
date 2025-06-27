/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:04:32 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:52:13 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <signal.h>
#include <readline/history.h>

#include "libft.h"
#include "shell.h"
#include "debug.h"
#include "free.h"
#include "signals.h"
#include "error.h"

#define RL_BUFFER_SIZE 100

void	run_readline(const char *prompt, int fd_write)
{
	char	*result;

	result = readline(prompt);
	if (!result)
	{
		print_debug("return of readline empty!");
		write(fd_write, "\n", 1);
	}
	else
		write(fd_write, result, ft_strlen(result));
}

char	*read_pipe_until_eof(int fd_read)
{
	int			chars;
	char		buffer[RL_BUFFER_SIZE + 1];
	char		*dup;
	t_str_list	*new;
	t_str_list	*buffers;

	buffers = NULL;
	chars = read(fd_read, buffer, RL_BUFFER_SIZE);
	while (chars > 0)
	{
		buffer[chars] = '\0';
		print_debug(buffer);
		dup = ft_strdup(buffer);
		new = (t_str_list *) ft_lstnew(dup);
		ft_lstadd_back((t_list **) &buffers, (t_list *) new);
		chars = read(fd_read, buffer, RL_BUFFER_SIZE);
	}
	dup = join_list_to_str(buffers);
	ft_lstclear((t_list **) &buffers, free);
	return (dup);
}

void	init_readline_fork(t_shell *shell, int rl_pipe[2], const char *prompt, \
	char *heredoc_free[2])
{
	t_history	*i;

	shell->readline_fork = fork();
	if (shell->readline_fork)
		return ;
	printf_debug("... starting readline fork ...\n");
	free(shell->total);
	if (heredoc_free[0])
		free(heredoc_free[0]);
	if (heredoc_free[1])
		free(heredoc_free[1]);
	if (heredoc_free[2])
		free(heredoc_free[2]);
	set_signals(&signal_handler_readline);
	if (shell->tokens)
		free_tokens(&shell->tokens);
	close(rl_pipe[0]);
	i = shell->history;
	while (i)
	{
		add_history(i->line);
		i = i->next;
	}
	run_readline(prompt, rl_pipe[1]);
	close(rl_pipe[1]);
	printf_debug("... ending readline fork ...\n");
	free_on_exit(shell, 1);
}

char	*wait_for_readline_exit(t_shell *shell, int rl_pipe[2])
{
	int		status;
	char	*rl_return;

	status = 0;
	close(rl_pipe[1]);
	waitpid(shell->readline_fork, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = -1;
	if (status != 1)
	{
		close(rl_pipe[0]);
		shell->readline_fork = -2;
		return (NULL);
	}
	rl_return = read_pipe_until_eof(rl_pipe[0]);
	close(rl_pipe[0]);
	return (rl_return);
}

char	*readline_fork(const char *prompt, t_shell *shell, char *heredoc_eof, \
	char *heredoc_free[2])
{
	int		rl_pipe[2];
	char	*rl_return;

	
	pipe(rl_pipe);
	init_readline_fork(shell, rl_pipe, prompt, (char *[]){heredoc_eof, \
		heredoc_free[0], heredoc_free[1]});
	if (shell->readline_fork == -1)
		return (NULL);
	if (!set(&rl_return, wait_for_readline_exit(shell, rl_pipe)))
		return (NULL);
	if (!ft_strcmp(rl_return, "\n"))
	{
		free(rl_return);
		if (heredoc_eof)
			return (rl_return = ft_strdup(heredoc_eof), \
			ft_cancel_newline_at_end(rl_return), \
			ft_eprintf(EMSG_HEREDOC_DELIM_BY_EOF, SHELL_NAME, \
				rl_return), free(rl_return), ft_strdup(heredoc_eof));
		free(shell->total);
		write(STDERR_FILENO, "exit\n", 5);
		free_on_exit(shell, 0);
	}
	shell->readline_fork = -2;
	return (rl_return);
}
