/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:07:31 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 20:10:51 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "cmd.h"
#include "shell.h"
#include "libft.h"
#include "debug.h"
#include "parse_env.h"
#include "free.h"
#include "execute.h"

static char	*handle_exit_status(char **old_str, t_shell *shell, int *i);
static char	*find_env_var(char **env, const char *var_name, size_t var_len);
static char	*process_variable(char *str, t_shell *shell, int *i);

/**
 * @brief Expands environment variables in a string
 * @details Processes a string containing environment variables (prefixed with $)
 * and replaces them with their values. Special handling for $? which returns
 * the last command's exit status. Variables not found in the environment are
 * replaced with empty strings.
 *
 * @param str The string containing variables to expand
 * @param shell Shell structure containing environment variables and last
 * command status
 * @return char* New allocated string with expanded variables,
 * NULL if allocation fails
 */
char	*expand_var(char *str, t_shell *shell)
{
	char	*expanded_str;

	printf_debug("before expand : %s", str);
	if (!ft_strcmp(str, "$?"))
		return (ft_itoa(shell->ret_last_cmd));
	if (ft_strchr(str, '$'))
		expanded_str = replace_expand_var(str, shell);
	else
		expanded_str = ft_strdup(str);
	if (!expanded_str)
		return (NULL);
	printf_debug("expanded var : %s\n", expanded_str);
	return (expanded_str);
}

/**
 * @brief Replaces and expands variables in a string
 *
 * @param old_str String containing variables to expand
 * @param shell Shell structure with environment
 * @return char* New string with expanded variables
 */
char	*replace_expand_var(char *old_str, t_shell *shell)
{
	char	*new_str;
	char	*temp;
	int		i;

	i = 0;
	new_str = NULL;
	while (old_str[i])
	{
		if (old_str[i] == '$' && old_str[i + 1] == '?'
			&& (i == 0 || old_str[i - 1] != '\\'))
		{
			temp = handle_exit_status(&new_str, shell, &i);
			free(new_str);
			new_str = temp;
		}
		else if (old_str[i] == '$' && (i == 0 || old_str[i - 1] != '\\'))
		{
			temp = process_variable(old_str, shell, &i);
			new_str = ft_strjoin_null(new_str, temp);
			free(temp);
		}
		else
			new_str = ft_strjoin_char(new_str, old_str[i++]);
	}
	return (new_str);
}

static char	*handle_exit_status(char **old_str, t_shell *shell, int *i)
{
	char	*temp;
	char	*new_str;

	temp = ft_itoa(shell->ret_last_cmd);
	new_str = ft_strjoin_null(*old_str, temp);
	free(temp);
	*i += 2;
	return (new_str);
}

/**
 * @brief Searches for an environment variable match
 * 
 * @param env Environment array to search in
 * @param var_name Variable name to look for
 * @param var_len Length of the variable name
 * @return char* Value of variable if found, NULL if not
 */
static char	*find_env_var(char **env, const char *var_name, size_t var_len)
{
	int	k;

	k = 0;
	while (env && env[k])
	{
		if (!ft_strncmp(var_name, env[k], var_len)
			&& env[k][var_len] == '=')
			return (env[k] + var_len + 1);
		k++;
	}
	return (NULL);
}

/**
 * @brief Process a single variable in the string
 * 
 * @param str Current position in string
 * @param shell Shell structure
 * @param i Position counter
 * @return char* Expanded variable value or NULL
 */
static char	*process_variable(char *str, t_shell *shell, int *i)
{
	int		j;
	char	*var_value;
	char	*new_str;

	j = 1;
	while (str[*i + j] && !ft_isspace(str[*i + j])
		&& str[*i + j] != '$')
		j++;
	var_value = find_env_var(shell->env, str + *i + 1, j - 1);
	if (var_value)
	{
		new_str = ft_strdup(var_value);
		*i += j;
		return (new_str);
	}
	*i += j;
	return (ft_strdup(""));
}
