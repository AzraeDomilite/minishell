/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_outside.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:36:54 by blucken           #+#    #+#             */
/*   Updated: 2025/05/05 11:37:33 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief check if needle is found in string outside quotes and round brackets
 * 
 * @param str heap in which to look for needle
 * @param needle string to look for
 * @param ignore_brackets if 1 only check if quotes are open, still look 
 * for needle inside opened brackets
 * @return position of first needle in str, if needle is found, else NULL
 */
char	*ft_strstr_outside(char *str, char *needle, int ignore_brackets)
{
	int		brackets;
	int		quotes;

	brackets = 0;
	quotes = 0;
	while (*str)
	{
		if (!quotes)
		{
			if ((!brackets || ignore_brackets) && \
			!ft_strncmp(str, needle, ft_strlen(needle)))
				return (str);
			if (*str == '(')
				brackets++;
			if (*str == ')')
				brackets--;
			if (brackets < 0 && !ignore_brackets)
				return (NULL);
		}
		manage_quotes(str, &quotes);
		str++;
	}
	return (NULL);
}

/**
 * @brief looks for several needles in str one after another, only if outside 
 * quotes and round brackets
 * 
 * @param str heap in which to look for needle
 * @param needles NULL-terminated array of strings to look for
 * @param ignore_brackets if 1 only check if quotes are open, still look for 
 * needle inside opened brackets
 * @return position of first needle in str, if needle is found, else NULL
 */
char	*ft_strstrs_outside(char *str, char *needles[], int ignore_brackets)
{
	char	*res;

	while (*needles)
	{
		res = ft_strstr_outside(str, *needles, ignore_brackets);
		if (res)
			return (res);
		needles++;
	}
	return (NULL);
}

/**
 * @brief check if needle is found in string outside quotes and round brackets, 
 * searching from the back of the string
 * 
 * @param str heap in which to look for needle
 * @param needle string to look for
 * @param ignore_brackets if 1 only check if quotes are open, still look for 
 * needle inside opened brackets
 * @return char* position of first needle in str from its end, 
 * if needle is found, else NULL
 */
char	*ft_strstr_outside_rev(char *str, char *needle, int ignore_brackets)
{
	int		brackets;
	int		quotes;
	char	*begin;

	begin = str;
	brackets = 0;
	quotes = 0;
	while (*str)
		str++;
	while (str >= begin)
	{
		if ((!brackets || ignore_brackets) && !quotes && \
		!ft_strncmp(str, needle, ft_strlen(needle)))
			return (str);
		if (*str == '(' && !quotes)
			brackets++;
		if (*str == ')' && !quotes)
			brackets--;
		if (!quotes && brackets > 0 && !ignore_brackets)
			return (NULL);
		manage_quotes(str, &quotes);
		str--;
	}
	return (NULL);
}

/**
 * @brief looks for several needles from end of str one after another, 
 * only if outside quotes and round brackets
 * 
 * @param str heap in which to look for needle
 * @param needles NULL-terminated array of strings to look for
 * @param ignore_brackets if 1 only check if quotes are open, still look for 
 * needle inside opened brackets
 * @return position of first needle in str from end, 
 * if needle is found, else NULL
 */
char	*ft_strstrs_outside_rev(char *str, char *needles[], int ignore_brackets)
{
	char	*res;

	while (*needles)
	{
		res = ft_strstr_outside_rev(str, *needles, ignore_brackets);
		if (res)
			return (res);
		needles++;
	}
	return (NULL);
}

/**
 * @brief looks for first match of several needles from end of str, 
 * only if outside quotes and round brackets
 * 
 * @param str heap in which to look for needle
 * @param needles NULL-terminated array of strings to look for
 * @param ignore_brackets if 1 only check if quotes are open, still look for 
 * needle inside opened brackets
 * @return position of first needle in str from end, 
 * if needle is found, else NULL
 */
char	*ft_strstrs_outside_first_rev(char *str, char *needles[], \
	int ignore_brackets)
{
	char	*res;

	res = str;
	while (*needles)
	{
		res = ft_strstr_outside_rev(str, *needles, ignore_brackets);
		if (res > str)
			str = res;
		needles++;
	}
	return (NULL);
}
