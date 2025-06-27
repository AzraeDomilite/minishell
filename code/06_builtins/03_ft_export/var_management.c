/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:50:14 by blucken           #+#    #+#             */
/*   Updated: 2025/02/13 13:24:00 by blucken          ###   ########.fr       */
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

/**
 * @brief add a variable to the environment if it does not exist
 * 
 * @param arg 
 * @param env 
 * @return char** 
 */
char	**add_var(char *arg, char **env)
{
	char	**new_env;
	int		i;

	new_env = add_last_tab(env, arg);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	sort_env(new_env);
	return (new_env);
}

/**
 * @brief check if a variable exists in the environment
 * 
 * @param arg 
 * @param env 
 * @return int 
 */
int	var_exist(char *arg, char **env)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = get_var_name(arg);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0)
		{
			free(var_name);
			return (1);
		}
		i++;
	}
	free(var_name);
	return (0);
}

/**
 * @brief replace a variable in the environment is it exists
 * 
 * @param arg 
 * @param env 
 * @return int 
 */
void	replace_var(char *arg, char **env)
{
	int		i;
	int		varlen;
	char	*var_name;

	var_name = get_var_name(arg);
	varlen = ft_strlen(var_name);
	free(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, varlen) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(arg);
			sort_env(env);
			return ;
		}
		i++;
	}
	return ;
}
