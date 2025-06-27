/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:31:18 by blucken           #+#    #+#             */
/*   Updated: 2025/06/24 11:46:16 by blucken          ###   ########.fr       */
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

/**
 * @brief Displays the environment variables.
 *
 * This function displays the environment variables stored in the `shell`
 * structure. It writes each variable followed by a newline character to the
 * specified file descriptor.
 *
 * @param args The arguments passed to the command (not used in this function).
 * @param fd_out The file descriptor to write the environment variables to.
 * @param shell The shell structure containing the environment variables.
 * @return 0 on success.
*/
int	ft_env(t_args *args, int fd_out, t_shell *shell)
{
	int	i;

	(void) shell;
	(void) args;
	i = 0;
	while (shell->env[i] && shell->env[i][0])
	{
		write(fd_out, shell->env[i], ft_strlen(shell->env[i]));
		write(fd_out, "\n", 1);
		i++;
	}
	return (0);
}
/**
 * @brief
 *
 * This function sort the environment variables in alphabetical order. This is
 * just to be close to the bash behavior.
 *
 * @param env
*/
void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}
