/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:27:51 by blucken           #+#    #+#             */
/*   Updated: 2025/05/02 10:27:51 by blucken          ###   ########.fr       */
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

t_match_array	*ft_init_match_array(void)
{
	t_match_array	*array;

	array = malloc(sizeof(t_match_array));
	if (!array)
		return (NULL);
	array->capacity = 20;
	array->count = 0;
	if (!set(&array->matches, malloc(array->capacity * sizeof(char *))))
		return (free(array), NULL);
	return (array);
}

void	ft_add_match(t_match_array *array, const char *match)
{
	char	**new_matches;

	if (array->count >= array->capacity)
	{
		array->capacity *= 2;
		if (!set(&new_matches, ft_realloc(array->matches, \
				array->capacity * sizeof(char *))))
			return ;
		array->matches = new_matches;
	}
	array->matches[array->count] = ft_strdup(match);
	if (array->matches[array->count])
		array->count++;
}
