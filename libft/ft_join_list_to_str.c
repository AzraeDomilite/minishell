/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_list_to_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:13:34 by baschnit          #+#    #+#             */
/*   Updated: 2025/05/05 11:40:05 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

/**
 * @brief joins a list of strings into one single string
 * 
 * @param start first list item to start with
 * @return char* joined string of all contents of list start
 */
char	*join_list_to_str(t_str_list *start)
{
	size_t		length;
	t_str_list	*i;
	char		*str;

	if (!start)
		return (ft_strdup(""));
	i = start;
	length = ft_strlen(start->str);
	while (i->next)
	{
		i = i->next;
		length += ft_strlen(i->str);
	}
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	i = start;
	str = ft_stpcpy(str, i->str);
	while (i->next)
	{
		i = i->next;
		str = ft_stpcpy(str, i->str);
	}
	return (str - length);
}
