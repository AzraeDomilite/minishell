/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_args_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:44:42 by blucken           #+#    #+#             */
/*   Updated: 2025/02/14 17:44:42 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "cmd.h"
#include "shell.h"
#include "libft.h"
#include "debug.h"
#include "parse_env.h"
#include "free.h"
#include "execute.h"

static size_t	count_args(t_cmd *cmd);
static char		**allocate_args_array(size_t size);
static bool		fill_args_array(char **tab, t_cmd *cmd);

/**
 * @brief Converts a command's arguments list into an array of strings
 * 
 * Creates a NULL-terminated array of strings containing the command name
 * and its arguments, suitable for use with execve().
 * 
 * @param cmd Pointer to the command structure
 * @return char** Array of strings, or NULL if allocation fails
 */
char	**args_list_to_tab(t_cmd *cmd)
{
	char	**tab;
	size_t	args_count;

	args_count = count_args(cmd);
	tab = allocate_args_array(args_count);
	if (!tab)
		return (NULL);
	if (!fill_args_array(tab, cmd))
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

/**
 * @brief Counts the number of arguments in a command
 * 
 * Traverses the linked list of arguments and returns the total count
 * 
 * @param cmd Pointer to the command structure
 * @return size_t Number of arguments
 */
static size_t	count_args(t_cmd *cmd)
{
	size_t	count;
	t_args	*tmp;

	count = 0;
	tmp = cmd->args;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

/**
 * @brief Allocates memory for the arguments array
 * 
 * Allocates space for size + 2 pointers (command name + args + NULL terminator)
 * 
 * @param size Number of arguments
 * @return char** Allocated array or NULL if allocation fails
 */
static char	**allocate_args_array(size_t size)
{
	char	**tab;

	tab = malloc(sizeof(char *) * (size + 2));
	if (!tab)
		return (NULL);
	return (tab);
}

/**
 * @brief Fills the allocated array with command name and arguments
 * 
 * Copies the command name and all arguments into the array.
 * The first element is the command name, followed by arguments,
 * and NULL-terminated.
 * 
 * @param tab Array to fill
 * @param cmd Command structure containing name and arguments
 * @return true if successful
 * @return false if memory allocation fails
 */
static bool	fill_args_array(char **tab, t_cmd *cmd)
{
	t_args	*tmp;
	int		i;

	tab[0] = ft_strdup(cmd->name);
	if (!tab[0])
		return (false);
	i = 1;
	tmp = cmd->args;
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->arg);
		if (!tab[i])
		{
			while (i > 0)
				free(tab[--i]);
			return (false);
		}
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (true);
}
