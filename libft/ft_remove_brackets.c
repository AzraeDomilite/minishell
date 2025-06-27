/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_brackets.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:38:16 by blucken           #+#    #+#             */
/*   Updated: 2025/05/05 11:42:29 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief remove surrounding white space (space or tab) 
 * and all outer matching round brackets
 *
 * @param str
 * @return const char*
*/
char	*ft_remove_pair_of_brackets(char *str)
{
	char	*end;
	char	*begin;
	int		brackets;
	int		quotes;

	str = ft_strip(str);
	if (!*str && *str != '(')
		return (str);
	end = str;
	while (*end)
		end++;
	end--;
	if (end == str || *end != ')')
		return (str);
	brackets = 0;
	quotes = 0;
	begin = str;
	while (str < end)
	{
		if (!quotes)
		{
			if (*str == '(')
				brackets++;
			if (*str == ')')
				brackets--;
			if (brackets < 0)
				return (NULL);
		}
		ft_manage_quotes(str, &quotes);
		if (brackets == 0)
			return (begin);
		str++;
	}
	str = ft_ptr_substr(begin + 1, end - 1);
	free(begin);
	return (str);
}

char	*ft_remove_all_outer_brackets(char *str)
{
	char	*previous;

	previous = ft_strdup(str);
	str = ft_remove_pair_of_brackets(previous);
	while (ft_strcmp(previous, str))
	{
		free(previous);
		previous = str;
		str = ft_remove_pair_of_brackets(previous);
	}
	free(previous);
	return (str);
}

// char	*ft_remove_brackets(const char *end)
// {
// 	const char	*begin;

// 	begin = end;
// 	while (*end)
// 		end++;
// 	if (*begin)
// 		end--;
// 	while (begin < end)
// 	{
// 		if (!ft_isblank(*begin) && !ft_isblank(*end)
// 		&& (*begin != '(' || *end != ')'))
// 			break ;
// 		if (*begin != '(' && ft_isblank(*begin))
// 			begin++;
// 		if (*end != ')' && ft_isblank(*end))
// 			end--;
// 		if (*begin == '(' && *end == ')')
// 		{
// 			begin++;
// 			end--;
// 		}
// 	}
// 	if (end < begin)
// 		return (ft_strdup(""));
// 	return (ft_ptr_substr(begin, end));
// }