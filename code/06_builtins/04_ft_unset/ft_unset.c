/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:11:44 by blucken           #+#    #+#             */
/*   Updated: 2025/03/03 14:11:48 by blucken          ###   ########.fr       */
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

static int	free_tab(char	**tab);

/**
 * Unsets an environment variable.
 *
 * This function unsets an environment variable by setting the corresponding
 * entry in the `shell->env` array to NULL. Then it shifts all the entries after
 *  the unset variable to the left. It NULL terminates the array at the end.
 *
 * @param args The arguments passed to the function.
 * @param fd_out The file descriptor for output.
 * @param shell The shell structure.
 * @return 0 on success. return fd_out on failure. WTF?????
 * (1 line of code fo (void)fd_out...)
*/
int	ft_unset(t_args *args, int fd_out, t_shell *shell)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	if (!set(&new_env, ft_calloc(get_env_len(shell->env) + 1, sizeof(char *))))
		return (fd_out);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], args->arg, ft_strlen(args->arg)) == 0 \
		&& shell->env[i][ft_strlen(args->arg)] == '=')
		{
			i++;
			continue ;
		}
		if (!set(&new_env[j], ft_strdup(shell->env[i])))
			return (free_tab(new_env));
		i++;
		j++;
	}
	new_env[j] = NULL;
	free_tab(shell->env);
	shell->env = new_env;
	return (0);
}

/**
 * @brief free tab, to be move in libft
 *
 * @param tab
 * @return void*
*/
static int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}
