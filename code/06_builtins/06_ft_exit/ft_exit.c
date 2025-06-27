/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:41:20 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 16:42:24 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

#include "cmd.h"
#include "libft.h"
#include "debug.h"
#include "shell.h"
#include "ft_export.h"
#include "free.h"
#include "history.h"
#include "builtins.h"

static bool	ft_str_is_numeric(const char	*str);

/**
 * @brief exit builtin remove close_debug before final push !!
 *
 * @param args
 * @param fd_out
 * @param shell
 * @return int
*/
int	ft_exit(t_args *args, int fd_out, t_shell *shell)
{
	int	exit_status;

	(void)fd_out;
	exit_status = 0;
	if (!shell->pipes && fd_out)
		write(STDERR_FILENO, "exit\n", 5);
	if (args && args->arg)
	{
		if (!ft_str_is_numeric(args->arg))
		{
			write(STDERR_FILENO, EXIT_NUM_ARG, ft_strlen(EXIT_NUM_ARG));
			exit_status = 2;
		}
		else if (args->next)
		{
			write(STDERR_FILENO, EXIT_TOO_MANY_ARGS, \
				ft_strlen(EXIT_TOO_MANY_ARGS));
			return (1);
		}
		else
			exit_status = ft_atoi(args->arg);
	}
	return (free_on_exit(shell, exit_status), 0);
}

static bool	ft_str_is_numeric(const char *str)
{
	if (!str || !*str)
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}
