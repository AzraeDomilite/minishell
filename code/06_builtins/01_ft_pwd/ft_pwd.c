/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:16:04 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 16:16:35 by blucken          ###   ########.fr       */
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

int	ft_pwd(t_args *args, int fd_out, t_shell *shell)
{
	char	*cwd;
	int		argc;

	(void) shell;
	argc = ft_lstsize((t_list *) args);
	if (argc > 0)
		return (1);
	cwd = getcwd(NULL, 0);
	printf_debug("current workind directory: %s\n", cwd);
	write(fd_out, cwd, ft_strlen(cwd));
	write(fd_out, "\n", 1);
	free(cwd);
	return (0);
}
