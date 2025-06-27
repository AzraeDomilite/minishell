/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:22:05 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 14:06:20 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_env.h"
#include "debug.h"

static char	*try_path_combination(const char *path_dir, const char *cmd_name);
static char	*try_all_paths(char **paths, const char *cmd_name);
static char	**get_paths_from_env(char **env);

/**
 * @brief Retrieves the full path of a command by searching in environment paths
 *
 * This function searches for the given command name in all directories specified
 * in the PATH environment variable. It handles the following cases:
 * - If no environment is available, returns the original command name
 * - If PATH is not found, returns the original command name
 * - If the command is found in PATH with execute permissions, returns full path
 * - If the command is not found in any PATH directory, returns original name
 *
 * @param name The command name to search for
 * @param shell The shell structure containing environment variables
 * @return char* Either the full path to the command or the original command name
 */
char	*get_cmd_path(char *name, t_shell *shell)
{
	char	**paths;
	char	*result;
	char	*cmd_name;

	cmd_name = ft_strdup(name);
	if (!shell->env)
		return (cmd_name);
	paths = get_paths_from_env(shell->env);
	if (!paths)
		return (cmd_name);
	result = try_all_paths(paths, cmd_name);
	ft_free_splits(paths);
	if (result)
	{
		free(cmd_name);
		return (result);
	}
	return (cmd_name);
}

/**
 * @brief Attempts to create and verify a command path
 *
 * @param path_dir Directory path to check
 * @param cmd_name Command name to append
 * @return char* Valid path if successful, NULL if not
 */
static char	*try_path_combination(const char *path_dir, const char *cmd_name)
{
	char	*part_path;
	char	*full_path;

	part_path = ft_strjoin(path_dir, "/");
	full_path = ft_strjoin(part_path, cmd_name);
	free(part_path);
	if (access(full_path, X_OK) == 0)
	{
		if (DEBUG_PARSE_ENV)
		{
			print_debug("path found :");
			print_debug(full_path);
		}
		return (full_path);
	}
	free(full_path);
	return (NULL);
}

/**
 * @brief Tries to find the command in all available paths
 *
 * @param paths Array of possible path directories
 * @param cmd_name Command name to search for
 * @return char* Valid path if found, NULL if not
 */
static char	*try_all_paths(char **paths, const char *cmd_name)
{
	char	*valid_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (DEBUG_PARSE_ENV)
		{
			print_debug("paths :");
			print_debug(paths[i]);
		}
		valid_path = try_path_combination(paths[i], cmd_name);
		if (valid_path)
			return (valid_path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Retrieves the paths from the environment variable "PATH". Basically, it
 * searches for the "PATH" variable in the environment variables array and
 * splits it by the ':' character.
 *
 * @param env The array of environment variables.
 * @return An array of strings containing the paths from the "PATH"
 * variable, or NULL if "PATH" is not found.
*/

static char	**get_paths_from_env(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

/**
 * @brief Retrieves the value of an environment variable
 * 
 * @param env The environment variables array
 * @param var_name The name of the variable to retrieve
 * @return char* The value of the variable, or NULL if not found
 */
char	*get_env_value(char **env, const char *var_name)
{
	int		i;
	size_t	var_len;

	if (!env || !var_name)
		return (NULL);
	var_len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, var_len) && env[i][var_len] == '=')
			return (env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}
