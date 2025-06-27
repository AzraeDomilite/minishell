/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:02:13 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 20:02:18 by blucken          ###   ########.fr       */
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
#include "signals.h"

static bool	args_checker(int ac)
{
	if (ac != 1)
		return (false);
	return (true);
}

static int	minishell_usage(void)
{
	write(STDERR_FILENO, "Usage : <./minishell> without any arguments\n", 44);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;

	if (!args_checker(ac))
		return (minishell_usage());
	(void) av;
	shell = init_shell(env);
	shell->tty = NULL;
	if (!shell->stdout_tty)
		rl_outstream = stderr;
	else
		rl_outstream = stdout;
	set_signals(&signal_handler_main);
	printf_debug("minishell started...\n");
	printf_debug("is it connected to a terminal? %i %i\n", \
	isatty(STDIN_FILENO), isatty(STDOUT_FILENO));
	minishell_loop(shell);
	printf_debug("this line should never be reached!!!");
	return (0);
}
