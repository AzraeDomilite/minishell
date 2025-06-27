/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:54:25 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 17:54:25 by blucken          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*target;
	char	*start;

	target = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	start = target;
	if (target == NULL)
		return (NULL);
	while (*s1)
	{
		*target = *s1;
		target++;
		s1++;
	}
	while (*s2)
	{
		*target = *s2;
		target++;
		s2++;
	}
	*target = '\0';
	return (start);
}
