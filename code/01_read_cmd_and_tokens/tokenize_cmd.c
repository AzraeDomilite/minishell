/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:45:31 by blucken           #+#    #+#             */
/*   Updated: 2025/02/14 13:38:27 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tokens.h"

/**
 * @brief	will add a substring between start and including end to the tokens
 * linked list
 *
 * @param tokens	Linked list of strings
 * @param start 	beginning of the new token
 * @param end 		end of the new token
 * @return			returns 1 if token has been created successfully, else 0
*/
int	add_token(t_tokens **tokens, char *start, char *end)
{
	t_tokens	*new;

	if (!set(&new, malloc(sizeof(t_tokens))))
		return (0);
	if (!set(&(new->token), ft_ptr_substr(start, end)))
		return (free(new), 0);
	new->next = NULL;
	ft_lstadd_back((t_list **) tokens, (t_list *) new);
	return (1);
}

/**
 * @brief check if str is equal to one of the operators ops
 *
 * @param str	String to be checked
 * @param ops 	Array of strings to which str will be compared
 * @return		Will return length of str if str is in ops, else 0
*/
int	has_operator(char *str, char *ops[])
{
	while (*ops)
	{
		if (!ft_strncmp(str, *ops, ft_strlen(*ops)))
			return (ft_strlen(*ops));
		ops++;
	}
	return (0);
}

/**
 * @brief helper function for tokenize_cmd
 *
 * On each iteration over a char in tokenize_cmd this function will be executed
 * and will check if there is an operator on the str pointer or will else set
 * the begin of a new token to the current str pointer. Lastly it will check for
 * open quotes on the current position.
 *
 * @param op		pointer to a variable that is 1 if there is
 * an operator on the current position
 * @param begin 	pointer to the begin of a new token other than an operator
 * @param quotes	0 if no quotes are open, 1 or 2 for single and double
 * quotes respectively
 * @param str		pointer to the current position in the command string
*/
void	initialise_quotes_ops_begin(int *op, char **begin, \
	int *quotes, char *str)
{
	*op = 0;
	if (!*quotes)
		*op = has_operator(str, (char *[12]){"||", "&&", \
			"<<", ">>", "|", "<", ">", ";", "(", ")", NULL});
	if (!*quotes && !*begin && !ft_isblank(*str) && !*op)
		*begin = str;
	ft_manage_quotes(str, quotes);
}

/**
 * @brief helper function for tokenize_cmd()
 * 
 * @param quotes	counter for quotes to initialise to 0
 * @param tokens	pointer to a tokens list initialised to NULL (empty list)
 * @param begin		pointer to a position in the command string (init to NULL)
 */
void	initialise_quotes_tokens_begin(int *quotes, t_tokens **tokens, \
	char **begin)
{
	*quotes = 0;
	*tokens = NULL;
	*begin = NULL;
}

/**
 * @brief splits a shell command into tokens
 *
 * A shell command consists of tokens that can be round brackets, operators or
 * other expressions (variable names, words or content between quotes) which are
 * separated by spaces or tabs.
 *
 * The function will split these tokens into a linked list of strings.
 *
 * @param str	String to be split into tokens
 * @return		Linked list of tokens
*/
t_tokens	*tokenize_cmd(char *str)
{
	int			quotes;
	int			op;
	char		*begin;
	t_tokens	*tokens;

	initialise_quotes_tokens_begin(&quotes, &tokens, &begin);
	while (*str)
	{
		initialise_quotes_ops_begin(&op, &begin, &quotes, str);
		if ((!quotes || !*(str + 1)) && begin && \
			(ft_isblank(*str) || !*(str + 1) || op))
		{
			add_token(&tokens, begin, str - ft_isblank(*str) - (op > 0));
			begin = NULL;
		}
		if (!quotes && op)
		{
			add_token(&tokens, str, str + op - 1);
			begin = NULL;
			str = str + op - 1;
		}
		str++;
	}
	return (tokens);
}
