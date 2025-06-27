/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:54:50 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:03:18 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "free.h"
#include "libft.h"
#include "shell.h"
#include "builtins.h"
#include "debug.h"
#include "history.h"
#include "ft_export.h"

t_builtins	*init_builtins(char *cmds[], void *funcs[])
{
	t_builtin	*builtin;
	t_builtins	*new;
	t_builtins	*list;

	list = NULL;
	while (*cmds)
	{
		if (!set(&builtin, malloc(sizeof(t_builtin))))
			return (ft_lstclear((t_list **) &list, (void (*)(void *)) \
			free_builtin), NULL);
		if (!set(&(builtin->name), ft_strdup(*cmds)))
			return (ft_lstclear((t_list **) &list, (void (*)(void *)) \
			free_builtin), free(builtin), NULL);
		builtin->func = *funcs;
		if (!set(&new, ft_lstnew(builtin)))
			return (ft_lstclear((t_list **) &list, (void (*)(void *)) \
			free_builtin), free_builtin(builtin), NULL);
		ft_lstadd_back((t_list **) &list, (t_list *) new);
		cmds++;
		funcs++;
	}
	return (list);
}

char	**init_env(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!set(&new_env[i], ft_strdup(env[i])))
			return (ft_free_splits(new_env), NULL);
		i++;
	}
	new_env[i] = NULL;
	return (set_shell_lvl(new_env), new_env);
}

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	if (!set(&shell, malloc(sizeof(t_shell))))
		return (NULL);
	ft_memset(shell, 0, sizeof(t_shell));
	if (!set(&(shell->builtins), init_builtins((char *[]){"echo", "cd", "pwd", \
	"export", "unset", "env", "exit", "history", NULL}, (void *[]){ft_echo, \
	ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit, ft_history, NULL})))
		return (free(shell), NULL);
	shell->env = init_env(env);
	update_pwd_var(shell);
	shell->buffer = NULL;
	shell->buffer_line = NULL;
	shell->lines = NULL;
	shell->tree = NULL;
	shell->tty = NULL;
	shell->stdin_tty = isatty(STDIN_FILENO);
	shell->stdout_tty = isatty(STDOUT_FILENO);
	shell->continue_loop = 1;
	shell->pipes = NULL;
	shell->history = NULL;
	shell->ret_last_cmd = 0;
	shell->readline_fork = -1;
	old_history_update(shell);
	return (shell);
}
