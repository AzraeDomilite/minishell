/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:08:43 by blucken           #+#    #+#             */
/*   Updated: 2025/04/26 19:02:19 by blucken          ###   ########.fr       */
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

static int	process_mods(t_mods *mods, t_shell *shell);
static void	process_var_expansion(t_qparser *p, char *arg, t_shell *shell);

char	*process_single_arg(char *arg, t_shell *shell)
{
	t_qparser	p;

	init_quotes_parser(&p, arg);
	while (arg[p.read_pos])
	{
		if ((arg[p.read_pos] == '"' || arg[p.read_pos] == '\'') && \
			(!p.in_squote || arg[p.read_pos] == '\'') && \
			(!p.in_dquote || arg[p.read_pos] == '"'))
		{
			handle_quotes(arg[p.read_pos], &p);
			p.read_pos++;
			continue ;
		}
		if (arg[p.read_pos] == '$' && !p.in_squote)
		{
			process_var_expansion(&p, arg, shell);
			continue ;
		}
		if (!((arg[p.read_pos] == '"' && !p.in_squote) || \
			(arg[p.read_pos] == '\'' && !p.in_dquote)))
			p.result[p.write_pos++] = arg[p.read_pos];
		p.read_pos++;
	}
	p.result[p.write_pos] = '\0';
	return (p.result);
}

int	expand_vars(t_node *node, t_shell *shell)
{
	char	*temp;
	t_args	*args;
	t_cmd	*cmd;

	cmd = node->cmd;
	temp = cmd->name;
	cmd->name = process_single_arg(temp, shell);
	free(temp);
	args = cmd->args;
	while (args)
	{
		temp = args->arg;
		args->arg = process_single_arg(temp, shell);
		free(temp);
		args = args->next;
	}
	return (process_mods(node->mods, shell));
}

static void	process_var_expansion(t_qparser *p, char *arg, t_shell *shell)
{
	char	*expanded;
	int		var_len;
	char	*var_name;

	if (arg[p->read_pos + 1] == '?')
	{
		expanded = handle_exit_status_qp(p, shell);
		free(expanded);
		return ;
	}
	var_len = get_var_length(arg, p->read_pos);
	var_name = ft_substr(arg, p->read_pos, var_len);
	expanded = expand_var(var_name, shell);
	free(var_name);
	var_name = NULL;
	handle_var_expansion(p, var_name, expanded);
	p->read_pos += var_len;
}

/**
 * @brief Process command modifiers for expansion
 * 
 * @param mods Modifiers list
 * @param shell Shell structure
 * @return int Success status
 */
static int	process_mods(t_mods *mods, t_shell *shell)
{
	char	*temp;

	while (mods)
	{
		if (mods->mod->type != HEREDOC)
		{
			temp = mods->mod->arg;
			mods->mod->arg = process_single_arg(temp, shell);
			free(temp);
		}
		mods = mods->next;
	}
	return (1);
}
