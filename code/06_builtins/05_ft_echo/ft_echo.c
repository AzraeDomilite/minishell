/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:12:19 by blucken           #+#    #+#             */
/*   Updated: 2025/04/27 19:12:56 by blucken          ###   ########.fr       */
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

static void	write_args(t_args *args, int fd_out);
static bool	is_n_flag(char *arg);

int	ft_echo(t_args *args, int fd_out, t_shell *shell)
{
	bool	n_flag;

	(void)shell;
	n_flag = false;
	if (!args)
	{
		write(fd_out, "\n", 1);
		return (0);
	}
	while ((ft_strncmp(args->arg, "-n", 2) == 0) && is_n_flag(args->arg))
	{
		if (!args->next)
			return (0);
		n_flag = true;
		if (args->next)
			args = args->next;
	}
	write_args(args, fd_out);
	if (!n_flag)
		write(fd_out, "\n", 1);
	return (0);
}

static bool	is_n_flag(char *arg)
{
	int	index;

	index = 2;
	while (arg && arg[index] && arg[index] == 'n')
		index++;
	if (arg[index])
		return (false);
	return (true);
}

static void	write_args(t_args *args, int fd_out)
{
	while (args)
	{
		write(fd_out, args->arg, ft_strlen(args->arg));
		args = args->next;
		if (args)
			write(fd_out, " ", 1);
	}
}
