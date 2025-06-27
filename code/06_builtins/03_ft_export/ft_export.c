/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:16:49 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 16:17:31 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "cmd.h"
#include "libft.h"
#include "debug.h"
#include "shell.h"
#include "ft_export.h"
#include "free.h"
#include "history.h"
#include "builtins.h"

#ifndef DEBUG_EXPORT
# define DEBUG_EXPORT 1
#endif

/**
 * @brief control if the variable is valid i.e. contains a '='
 *
 * @param arg
 * @return true
 * @return false
*/
bool	is_var_valid(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i] || (size_t)i == ft_strlen(arg))
		return (false);
	return (true);
}

/**
 * @brief export builtin
 *
 * @param args
 * @param fd_out
 * @param shell
 * @return int
*/
int	ft_export(t_args *args, int fd_out, t_shell *shell)
{
	if (!args || !args->arg)
		return (print_env_export(fd_out, shell));
	else if (!is_var_valid(args->arg))
		return (1);
	else if (args->arg && var_exist(args->arg, shell->env))
	{
		replace_var(args->arg, shell->env);
		return (0);
	}
	else if (args->arg)
		shell->env = add_var(args->arg, shell->env);
	return (0);
}

/**
 * @brief add a string to the end of a tab maybe add this to libft
 *
 * @param tab
 * @param str
 * @return char**
*/
char	**add_last_tab(char **tab, char *str)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	if (!set(&new_tab, malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
			return (ft_free_splits(new_tab));
		i++;
	}
	new_tab[i] = ft_strdup(str);
	if (!new_tab[i])
		return (ft_free_splits(new_tab));
	new_tab[i + 1] = NULL;
	return (new_tab);
}
