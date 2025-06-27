/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:23:34 by baschnit          #+#    #+#             */
/*   Updated: 2025/02/13 17:28:01 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_CMD_H
# define CHECK_CMD_H

# include "tokens.h"

int		check_syntax(t_tokens *tokens);
char	*check_completeness(t_tokens *tokens);

#endif