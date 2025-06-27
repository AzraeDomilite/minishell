/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:20:45 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:23:22 by blucken          ###   ########.fr       */
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
#include "ft_snprintf.h"

#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>

static char				**expand_wildcards(char *arg);
static t_match_array	*ft_find_wildcard_matches(const char *pattern, \
							const char *path);
static void				ft_process_directory_entries(DIR *dir, \
							const char *path, const char *pattern, \
							t_match_array *matches);

/**
 * @brief Expands a command containing wildcards to the first matched filename
 * @param cmd The command string potentially containing wildcards
 * @return If matches are found, returns the first match;
 *         otherwise, returns a duplicate of the original string.
 */
char	*expand_cmd_wildcards(char *cmd)
{
	char	**matches;
	char	*tmp;

	matches = expand_wildcards(cmd);
	if (!matches || !matches[0])
	{
		if (!set(&cmd, ft_strdup(cmd)))
			return (ft_free_splits(matches), NULL);
		return (cmd);
	}
	if (!set(&tmp, ft_strdup(matches[0])))
		return (ft_free_splits(matches), NULL);
	return (ft_free_splits(matches), tmp);
}

/**
 * @brief Expands wildcards in an argument and creates a linked list
 * of arguments
 * @param args The argument node to start with
 * @param expanded The string containing wildcards to be expanded
 * @return The head of the argument list with all wildcard expansions added
 *         Returns the original args on failure or if no matches found
 * @note The first match replaces the content of the original arg,
 *       additional matches are added as new arg nodes
 */
t_args	*process_wildcards(t_args *args, char *expanded)
{
	char	**matches;
	int		i;
	t_args	*current;
	t_args	*new_arg;

	matches = expand_wildcards(expanded);
	if (!matches || !matches[0])
		return (args);
	current = args;
	i = -1;
	while (matches[++i])
	{
		if (i == 0)
			current->arg = ft_strdup(matches[i]);
		else
		{
			if (!set(&new_arg, malloc(sizeof(t_args))))
				return (ft_free_splits(matches), args);
			new_arg->arg = ft_strdup(matches[i]);
			new_arg->next = NULL;
			current->next = new_arg;
			current = new_arg;
		}
	}
	return (ft_free_splits(matches), args);
}

static t_match_array	*ft_find_wildcard_matches(const char *pattern, \
							const char *path)
{
	DIR				*dir;
	t_match_array	*matches;

	matches = ft_init_match_array();
	if (!matches)
		return (NULL);
	dir = opendir(path);
	if (!dir)
	{
		perror("Unable to open directory");
		ft_free_match_array(matches);
		return (NULL);
	}
	ft_process_directory_entries(dir, path, pattern, matches);
	closedir(dir);
	ft_sort_matches(matches);
	return (matches);
}

/**
 * @brief Processes directory entries to find matches based on a given pattern.
 * 
 * This function iterates through the entries of a directory, filters 
 * them based on specific criteria (e.g., skipping "." and "..", 
 * handling hidden files, and matching a pattern), and adds matching 
 * entries to the provided match array.
 * 
 * @param dir Pointer to the directory stream to be read.
 * @param path The path to the directory being processed.
 * @param pattern The pattern to match against directory entries.
 * @param matches Pointer to the structure where matching entries will 
 * be stored.
 * 
 * @note Hidden files (starting with '.') are ignored unless the pattern itself
 *       starts with a '.'.
 * @note The function uses `snprintf` to construct the full path of each entry.
 *       Consider replacing `snprintf` with a custom implementation or
 * 		 a specific version for wildcards as indicated in the warning.
 * 
 * @warning Ensure that the buffer size (PATH_MAX) is sufficient for 
 * 			the full path.
 *          Replace `snprintf` with a safer or more specific implementation 
 * 			if needed.
 */
static void	ft_process_directory_entries(DIR *dir, \
				const char *path, const char *pattern, \
				t_match_array *matches)
{
	struct dirent	*entry;
	struct stat		file_stat;
	char			full_path[PATH_MAX];

	entry = readdir(dir);
	while (entry)
	{
		if (ft_strcmp(entry->d_name, ".") == 0 || \
			ft_strcmp(entry->d_name, "..") == 0)
		{
			entry = readdir(dir);
			continue ;
		}
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		ft_snprintf(full_path, PATH_MAX, "%s/%s", path, entry->d_name);
		if (stat(full_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode) && \
			ft_matches_pattern(pattern, entry->d_name))
			ft_add_match(matches, entry->d_name);
		entry = readdir(dir);
	}
}

static char	**expand_wildcards(char *arg)
{
	t_match_array	*matches;
	char			**result;
	int				i;

	matches = ft_find_wildcard_matches(arg, ".");
	if (!matches || matches->count == 0)
		return (ft_free_match_array(matches), NULL);
	if (!set(&result, malloc((matches->count + 1) * sizeof(char *))))
		return (ft_free_match_array(matches), NULL);
	i = -1;
	while (++i < matches->count)
		result[i] = ft_strdup(matches->matches[i]);
	result[i] = NULL;
	ft_free_match_array(matches);
	return (result);
}
