/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:53:12 by blucken           #+#    #+#             */
/*   Updated: 2025/03/03 16:53:12 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef struct s_tokens
{
	char			*token;
	struct s_tokens	*next;
}	t_tokens;

void		free_token(t_tokens *tokens);
void		free_tokens(t_tokens **tokens);
int			has_operator(char *str, char *ops[]);
void		print_tokens(t_tokens *tokens);
t_tokens	*tokenize_cmd(char *str);

#endif