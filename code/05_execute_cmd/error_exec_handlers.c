/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec_handlers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:23:50 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:56:01 by baschnit         ###   ########.fr       */
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

pid_t	fork_error(void)
{
	perror("fork");
	return (-1);
}

pid_t	args_tab_error(char	*cmd_path, t_shell *shell)
{
	perror("args_list_to_tab");
	if (cmd_path)
		free(cmd_path);
	free_shell(shell);
	exit(EXIT_FAILURE);
}

void	dup2_error(char *cmd_path, t_shell *shell)
{
	perror("dup2");
	free(cmd_path);
	free_shell(shell);
	exit(EXIT_FAILURE);
}
