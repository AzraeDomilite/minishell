/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:12:21 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:12:29 by blucken          ###   ########.fr       */
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

void	free_on_exit(t_shell *shell, int ret)
{
	close_debug_fd();
	update_history_file(shell);
	free_shell(shell);
	rl_clear_history();
	exit(ret & 255);
}
