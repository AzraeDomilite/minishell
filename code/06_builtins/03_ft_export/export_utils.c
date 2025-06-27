/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 21:30:01 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 21:30:01 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "cmd.h"
#include "libft.h"
#include "debug.h"
#include "shell.h"
#include "ft_export.h"

/**
 * @brief Get the var name object
 * 
 * @param arg 
 * @return char* 
 */
char	*get_var_name(char *arg)
{
	int		i;
	char	*var_name;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i] || (size_t)i == ft_strlen(arg))
		return (NULL);
	var_name = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		var_name[i] = arg[i];
		i++;
	}
	var_name[i] = '=';
	var_name[i + 1] = '\0';
	return (var_name);
}

/**
 * @brief Get the env len object
 * 
 * @param env 
 * @return size_t 
 */
size_t	get_env_len(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/**
 * @brief Get the var pos object
 * 
 * @param env 
 * @param var_name 
 * @return size_t 
 */
size_t	get_var_pos(char **env, char *var_name)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	print_env_export(int fd_out, t_shell *shell)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (shell->env[i] && shell->env[i][0])
	{
		j = 0;
		k = 0;
		write(fd_out, "declare -x ", 11);
		while (shell->env[i][j] != '=')
			j++;
		while (k <= j)
			write(fd_out, &shell->env[i][k++], 1);
		write(fd_out, "\"", 1);
		j++;
		while (shell->env[i][j])
			write(fd_out, &shell->env[i][j++], 1);
		write(fd_out, "\"", 1);
		write(fd_out, "\n", 1);
		i++;
	}
	return (0);
}
