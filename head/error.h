/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:33:07 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:35:01 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define EMSG_PARSE_CLOSED_RBRACKET "parse error near `)'"
# define EMSG_PARSE_OPEN_RBRACKET "parse error near `('"

# define EMSG_HEREDOC_DELIM_BY_EOF \
"-%s: warning: here-document delimited by end-of-file (wanted `%s')\n"
# define EMSG_SYNTAX_UNEXPECTED_EOF "-%s: syntax error: unexpected end of file\n"

#endif