/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:01:07 by blucken           #+#    #+#             */
/*   Updated: 2025/04/26 19:01:08 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "shell.h"
#include "libft.h"
#include "parse_env.h"
#include "free.h"
#include "execute.h"
#include "debug.h"

#include <string.h>

void	init_quotes_parser(t_qparser *p, char *arg)
{
	p->in_dquote = false;
	p->in_squote = false;
	p->read_pos = 0;
	p->write_pos = 0;
	p->result = malloc(ft_strlen(arg) * 4 + 1);
}

void	handle_quotes(char c, t_qparser *p)
{
	if (c == '"')
		p->in_dquote = !p->in_dquote;
	else if (c == '\'')
		p->in_squote = !p->in_squote;
}

char	*handle_exit_status_qp(t_qparser *p, t_shell *shell)
{
	char	*expanded;

	expanded = ft_itoa(shell->ret_last_cmd);
	ft_strcpy(p->result + p->write_pos, expanded);
	p->write_pos += ft_strlen(expanded);
	p->read_pos += 2;
	return (expanded);
}

int	get_var_length(char *arg, int start_pos)
{
	int	var_len;

	var_len = 1;
	while (arg[start_pos + var_len] && \
		(ft_isalnum(arg[start_pos + var_len]) || \
		arg[start_pos + var_len] == '_'))
		var_len++;
	return (var_len);
}

void	handle_var_expansion(t_qparser *p, char *var_name, char *expanded)
{
	(void)var_name;
	if (expanded)
	{
		ft_strcpy(p->result + p->write_pos, expanded);
		p->write_pos += ft_strlen(expanded);
		free(expanded);
	}
}
