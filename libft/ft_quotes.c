/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:39:32 by blucken           #+#    #+#             */
/*   Updated: 2025/05/05 11:39:35 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	increases brackets pointer value by one for opening bracket and
 * reduces pointer value for closing bracket
 *
 * Parameter str has to have valid bracket syntax (no closing bracket before
 * opening bracket)
 *
 * @param str 		String of which brackets will be counted
 * @param quotes 	Indicator if for the current str pointer quotes
 * are open or not
 * @param brackets	Pointer to count of open brackets
*/
void	ft_manage_brackets(char *str, int quotes, int *brackets)
{
	if (!quotes)
	{
		if (*str == '(')
			(*brackets)++;
		if (*str == ')')
			(*brackets)--;
	}
}

/**
 * @brief helper function for functions that keep track of quotes while 
 * looping over a string
 * 
 * @param str pointer to string pointer, that holds current position of loop
 * @param quotes status of quotes. 0: no quotes open. 1: single quotes open. 
 * 2: double quotes open.
 */
void	ft_manage_quotes(char *str, int *quotes)
{
	if (*str == '\'' && *quotes != 2)
	{
		if (*quotes == 1)
			*quotes = 0;
		else
			*quotes = 1;
	}
	if (*str == '"' && *quotes != 1)
	{
		if (*quotes == 2)
			*quotes = 0;
		else
			*quotes = 2;
	}
}

/**
 * @brief checks for open quotes in string
 * 
 * @param str		str to check for open quotes
 * @return			0 if no quotes open, 1 if single quotes open,
 * 					2 if double quotes open
 */
int	ft_check_quotes(char *str)
{
	int	quotes;

	quotes = 0;
	while (*str)
	{
		ft_manage_quotes(str, &quotes);
		str++;
	}
	return (quotes);
}
