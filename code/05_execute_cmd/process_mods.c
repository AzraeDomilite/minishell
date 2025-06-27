/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_mods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:28:16 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:28:18 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "shell.h"
#include "libft.h"
#include "parse_env.h"
#include "free.h"
#include "execute.h"
#include "debug.h"
#include "wildcards.h"

/**
 * @brief Process command modifiers for expansion
 * 
 * @param mods Modifiers list
 * @param shell Shell structure
 * @return int Success status
 */
int	process_mods(t_mods *mods, t_shell *shell)
{
	char	*temp;

	while (mods)
	{
		if (mods->mod->type != HEREDOC)
		{
			temp = mods->mod->arg;
			mods->mod->arg = process_single_arg(temp, shell);
			free(temp);
		}
		mods = mods->next;
	}
	return (1);
}
