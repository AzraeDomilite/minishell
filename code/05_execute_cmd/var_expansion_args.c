/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:28:57 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:30:07 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "shell.h"
#include "libft.h"
#include "parse_env.h"
#include "free.h"
#include "execute.h"
#include "debug.h"
#include "wildcards.h"

static void	process_var_expansion(t_qparser *p, char *arg, t_shell *shell);

char	*expand_var_heredoc(char *eof, char *line, t_shell *shell)
{
	char	*ret;

	if (ft_strchr(eof, '\'') || ft_strchr(eof, '\"'))
		return (line);
	ret = process_single_arg(line, shell);
	free(line);
	return (ret);
}

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
		else if (arg[p.read_pos] == '$' && !p.in_squote && \
			arg[p.read_pos + 1] && arg[p.read_pos + 1] != '_' \
			&& arg[p.read_pos + 1] != '\"')
			process_var_expansion(&p, arg, shell);
		else if (!((arg[p.read_pos] == '"' && !p.in_squote) || \
			(arg[p.read_pos] == '\'' && !p.in_dquote)))
			p.result[p.write_pos++] = arg[p.read_pos];
		p.read_pos++;
	}
	p.result[p.write_pos] = '\0';
	return (p.result);
}

void	expand_cmd_name_vars(char **cmd_name, t_shell *shell)
{
	char	*temp;

	if (!*cmd_name)
		return ;
	temp = *cmd_name;
	*cmd_name = process_single_arg(temp, shell);
	free(temp);
	temp = *cmd_name;
	*cmd_name = expand_cmd_wildcards(*cmd_name);
	free(temp);
}

int	expand_vars(t_node *node, t_shell *shell)
{
	char	*temp;
	t_args	*args;
	bool	is_quoted;

	expand_cmd_name_vars(&node->cmd->name, shell);
	is_quoted = false;
	args = node->cmd->args;
	while (args)
	{
		temp = args->arg;
		if (*args->arg == '\"' || *args->arg == '\'')
			is_quoted = true;
		args->arg = process_single_arg(temp, shell);
		free(temp);
		if (!is_quoted)
			args = process_wildcards(args, args->arg);
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
