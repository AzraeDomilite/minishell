/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:24:55 by blucken           #+#    #+#             */
/*   Updated: 2025/05/02 10:24:55 by blucken          ###   ########.fr       */
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

t_builtin	*in_builtins(char *cmd, t_builtins *builtins)
{
	if (!cmd)
		return (NULL);
	while (builtins)
	{
		if (!ft_strcmp(builtins->builtin->name, cmd))
			return (builtins->builtin);
		builtins = builtins->next;
	}
	return (NULL);
}

static char	*extract_level_str(const char *env_var)
{
	return (ft_substr(env_var, 6, ft_strlen(env_var) - 6));
}

static char	*create_new_shlvl(int level)
{
	char	*level_str;
	char	*new_var;

	level_str = ft_itoa(level + 1);
	if (!level_str)
		return (NULL);
	new_var = ft_strjoin("SHLVL=", level_str);
	free(level_str);
	return (new_var);
}

static void	update_shlvl(char **env, int index)
{
	char	*level_str;
	int		level;
	char	*new_var;

	level_str = extract_level_str(env[index]);
	if (!level_str)
		return ;
	level = ft_atoi(level_str);
	free(level_str);
	new_var = create_new_shlvl(level);
	if (!new_var)
		return ;
	free(env[index]);
	env[index] = new_var;
}

void	set_shell_lvl(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			update_shlvl(env, i);
			return ;
		}
		i++;
	}
}
