/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:51:15 by blucken           #+#    #+#             */
/*   Updated: 2025/03/03 13:51:19 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "cmd.h"
#include "tree.h"
#include "libft.h"
#include "tokens.h"
#include "free.h"

void	free_token(t_tokens *tokens)
{
	free(tokens->token);
	free(tokens);
}

void	free_tokens(t_tokens **tokens)
{
	ft_lstclear((t_list **) tokens, free);
}

void	free_mod(t_mod *mod)
{
	free(mod->arg);
	free(mod);
}

void	free_mods(t_mods **mods)
{
	ft_lstclear((t_list **) mods, (void (*)(void *)) free_mod);
}
