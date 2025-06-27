/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:50:20 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 13:51:51 by blucken          ###   ########.fr       */
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

/**
 * @brief 
 * 
 * This function will join a string with a single character.
 * 
 * @param str 
 * @param c 
 * @return char* 
 */
char	*ft_strjoin_char(char *str, char c)
{
	char	*new_str;
	int		len;

	if (!str)
		len = 0;
	else
		len = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	if (str)
		ft_strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}

/**
 * @brief return a pointer the last character of a string.
 * can be add to a utils or libft
 * @param str 
 * @return char* 
 */
char	*ft_strend(char *str)
{
	if (!*str)
		return (str);
	while (*str)
		str++;
	str--;
	return (str);
}

/**
 * @brief 
 * 
 * This function will join two strings together,
 * if one of the strings is NULL, it will
 * return a copy of the other string.
 * 
 * If both strings are NULL, it will return NULL.
 * 
 * It's build specifically to handle NULL strings.
 * 
 * @param s1 
 * @param s2 
 * @return char* 
 */
char	*ft_strjoin_null(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	if (s1)
		ft_stpcpy(str, s1);
	if (s2)
		ft_stpcpy(str + len1, s2);
	str[len1 + len2] = '\0';
	return (str);
}

bool	builtin_change_sh_state(char *name)
{
	if (!name)
		return (false);
	if (ft_strcmp(name, "exit") == 0 || \
		ft_strcmp(name, "cd") == 0 || \
		ft_strcmp(name, "export") == 0 || \
		ft_strcmp(name, "unset") == 0)
		return (true);
	return (false);
}

void	check_access(t_cmd *cmd, char *cmd_path, t_shell *shell)
{
	if (access(cmd_path, X_OK) == -1)
	{
		write(STDERR_FILENO, "-", 1);
		write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, cmd->name, ft_strlen(cmd->name));
		write(STDERR_FILENO, ": command not found\n", 20);
		if (DEBUG_EXECUTE_CMD)
		{
			print_debug("command not found :");
			print_debug(cmd->name);
		}
		free(cmd_path);
		free_shell(shell);
		exit(EXIT_CMD_NOT_FOUND);
	}
}
