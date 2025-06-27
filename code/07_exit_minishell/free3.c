/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:53:16 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 15:01:36 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
#include "free.h"

void	free_builtin(t_builtin *builtin)
{
	if (!builtin)
		return ;
	if (builtin->name)
		free(builtin->name);
	free(builtin);
}

void	free_pipes(t_plist **pipes)
{
	ft_lstclear((t_list **) pipes, free);
	pipes = NULL;
}

void	free_buffer(t_shell *shell)
{
	print_debug("starting to free buffer");
	if (shell->buffer)
		ft_free_splits(shell->buffer);
	shell->buffer = NULL;
	shell->buffer_line = NULL;
	print_debug("ending to free buffer");
}

void	free_history(t_history *history)
{
	t_history	*current;
	t_history	*next;

	current = history;
	while (current)
	{
		next = current->next;
		free(current->line);
		free(current);
		current = next;
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->history)
	{
		free_history(shell->history);
		shell->history = NULL;
	}
	rl_clear_history();
	free_buffer(shell);
	ft_lstclear((t_list **) &(shell->builtins), \
	(void (*)(void *)) free_builtin);
	ft_lstclear((t_list **) &(shell->lines), free);
	free_ctree(&(shell->tree));
	free_pipes(&(shell->pipes));
	if (shell->env)
		ft_free_splits(shell->env);
	if (shell->tty)
		fclose(shell->tty);
	free(shell);
}
