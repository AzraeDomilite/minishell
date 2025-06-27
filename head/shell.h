/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:07:12 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 19:00:35 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdbool.h>

# include "pipe.h"
# include "cmd.h"
# include "lines.h"
# include "tree.h"
# include "history.h"
# include "tokens.h"
# define SHELL_NAME "bash"

typedef struct s_shell	t_shell;

typedef struct t_builtin
{
	char	*name;
	int		(*func)(t_args *, int, t_shell	*);
}			t_builtin;

typedef struct s_builtins
{
	t_builtin			*builtin;
	struct s_builtins	*next;
}						t_builtins;

typedef struct s_shell
{
	char		**buffer;
	char		**buffer_line;
	int			continue_loop;
	int			ret_last_cmd;
	char		**env;
	FILE		*tty;
	int			stdin_tty;
	int			stdout_tty;
	t_lines		*lines;	
	t_ctree		*tree;
	t_plist		*pipes;
	t_builtins	*builtins;
	t_history	*history;
	int			readline_fork;
	char		*total;
	t_tokens	*tokens;
}				t_shell;

t_shell		*init_shell(char **env);
t_builtin	*in_builtins(char *cmd, t_builtins *builtins);
char		**init_env(char **env);
void		set_shell_lvl(char **env);
void		minishell_loop(t_shell *shell);

#endif