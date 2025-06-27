/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_modifiers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:26:32 by blucken           #+#    #+#             */
/*   Updated: 2025/03/03 14:26:48 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "free.h"
#include "shell.h"
#include "tokens.h"
#include "libft.h"
#include "free.h"

/**
 * @brief duplicates a token and adds it to the back of a list of tokens
 *
 * @param tokens	list of tokens to add the duplicated token to
 * @param token		pointer to a list element with the token to duplicate
 * @return int		returns 1 in case of success, 0 in case of error
*/
int	tokens_add_copy(t_tokens **tokens, t_tokens *token)
{
	t_tokens	*new;

	if (!set(&new, malloc(sizeof(t_tokens))))
		return (0);
	new->next = NULL;
	if (!set(&(new->token), ft_strdup(token->token)))
		return (free(new), 0);
	ft_lstadd_back((t_list **) tokens, (t_list *) new);
	return (1);
}

/**
 * @brief adds a modifier to an existing list of modifiers
 *
 * Modifiers (e.g. > file1) change the stdin or stdout to a file or heredoc.
 *
 * A modifier has a type according to its operator (<, >, << or >>) and an
 * argumente (a filename or a heredoc terminator). The argument will be
 * extracted from the function argument tokens.
 *
 * @param mods		list of modifiers preceding the modifier to add
 * @param mtype		type of the modifier to add, according to its operator
 * @param tokens	list of tokens with the first list element pointing to
 * operator of the current modifier
 * @return int 		return 1 in case of success, 0 in case of an error
*/
int	mods_add_mod(t_mods **mods, t_mtype mtype, t_tokens **tokens)
{
	t_mods	*mod;

	if (!set(&mod, malloc(sizeof(t_mods))))
		return (0);
	mod->next = NULL;
	if (!set(&(mod->mod), malloc(sizeof(t_mod))))
		return (free(mod), 0);
	mod->mod->type = mtype;
	if (!set(&(mod->mod->arg), ft_strdup((*tokens)->next->token)))
		return (free(mod->mod), free(mod), 0);
	*tokens = (*tokens)->next;
	ft_lstadd_back((t_list **) mods, (t_list *) mod);
	return (1);
}

/**
 * @brief helper function for function parse_mod_tokens
 *
 * initialises the count of brackets at the beginning of the tokens to 0, sets
 * tokens_after to a NULL pointer (empty list) and the list of found mods to a
 * NULL pointer (empty list)
 *
 * @param brackets		pointer to the count of open brackets in tokens
 * @param tokens_after	new list of tokens with modifiers removed
 * @param mods			list of modifiers extracted from the old list of tokens
*/
void	init_parse_mod_tokens(int *brackets, t_tokens **tokens_after, \
t_mods **mods)
{
	*brackets = 0;
	*tokens_after = NULL;
	*mods = NULL;
}

/**
 * @brief checks a string for a modifier operator and return the modifier type
 *
 * @param str		string to be checked for a modifier operator
 * @return t_mtype	returns the type of modifier in case an operator was found
*/
t_mtype	get_modifier_type(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(str, ">>", 2))
		return (OUTFILE_APPEND);
	if (!ft_strncmp(str, "<", 1))
		return (INFILE);
	if (!ft_strncmp(str, ">", 1))
		return (OUTFILE);
	return (NONE);
}

/**
 * @brief extracts all modifiers from a list of tokens
 *
 * This function will create a list of modifiers (modifying stdin and stdout to
 * files) from the original token list and will then change that token list to a
 *  new token list without the modifier tokens.
 *
 * @param tokens_before tokens double pointer to the original token list
 * including the modifiers
 * @return t_mods* pointer to the newly created list of modifiers
*/
t_mods	*parse_mods(t_tokens **tokens_before)
{
	t_mtype		mod;
	t_mods		*mods;
	t_tokens	*tokens;
	t_tokens	*tokens_after;
	int			brackets;

	init_parse_mod_tokens(&brackets, &tokens_after, &mods);
	tokens = *tokens_before;
	while (tokens)
	{
		if (!ft_strcmp(tokens->token, "("))
			brackets++;
		if (!ft_strcmp(tokens->token, ")"))
			brackets--;
		mod = get_modifier_type(tokens->token);
		if (brackets || mod == NONE)
			if (!tokens_add_copy(&tokens_after, tokens))
				return (free_mods(&mods), free_tokens(&tokens_after), NULL);
		if (!brackets && mod != NONE)
			if (!mods_add_mod(&mods, mod, &tokens))
				return (free_mods(&mods), free_tokens(&tokens_after), NULL);
		tokens = tokens->next;
	}
	*tokens_before = tokens_after;
	return (mods);
}
