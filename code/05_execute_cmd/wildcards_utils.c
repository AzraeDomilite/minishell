/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:27:03 by blucken           #+#    #+#             */
/*   Updated: 2025/05/02 10:27:07 by blucken          ###   ########.fr       */
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

#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>

void	ft_free_match_array(t_match_array *array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < array->count)
	{
		free(array->matches[i]);
		i++;
	}
	free(array->matches);
	free(array);
}

void	ft_sort_matches(t_match_array *array)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < array->count - 1)
	{
		j = i + 1;
		while (j < array->count)
		{
			if (ft_strcmp(array->matches[i], array->matches[j]) > 0)
			{
				temp = array->matches[i];
				array->matches[i] = array->matches[j];
				array->matches[j] = temp;
			}
			j++;
		}
		i++;
	}
}

bool	ft_match_star(const char *pattern, const char *filename)
{
	while (*pattern == '*')
		pattern++;
	if (*pattern == '\0')
		return (true);
	while (*filename != '\0')
	{
		if (ft_matches_pattern(pattern, filename))
			return (true);
		filename++;
	}
	return (false);
}

bool	ft_matches_pattern(const char *pattern, const char *filename)
{
	if (*pattern == '\0' && *filename == '\0')
		return (true);
	if (*pattern == '*')
		return (ft_match_star(pattern, filename));
	if (*pattern == '?' || *pattern == *filename)
		return (ft_matches_pattern(pattern + 1, filename + 1));
	return (false);
}
