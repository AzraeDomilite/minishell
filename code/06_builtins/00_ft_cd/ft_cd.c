/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:06:08 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:06:34 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

#include "cmd.h"
#include "libft.h"
#include "debug.h"
#include "shell.h"
#include "ft_export.h"
#include "free.h"
#include "history.h"
#include "builtins.h"

int	ft_cd(t_args *args, int fd_out, t_shell *shell)
{
	int		argc;

	(void) fd_out;
	(void) shell;
	argc = ft_lstsize((t_list *) args);
	if (argc != 1)
		return (-1);
	argc = (chdir(args->arg));
	if (argc)
		argc = 1;
	update_pwd_var(shell);
	return (argc);
}

void	update_pwd_var(t_shell *shell)
{
	char	*pwd;
	char	*cwd;

	if (!set(&cwd, getcwd(NULL, 0)))
		return ;
	if (!set(&pwd, ft_strjoin("PWD=", cwd)))
		return (free(cwd));
	free(cwd);
	if (!is_var_valid(pwd))
	{
		free(pwd);
		return ;
	}
	else if (pwd && var_exist(pwd, shell->env))
		replace_var(pwd, shell->env);
	else
		shell->env = add_var(pwd, shell->env);
	free(pwd);
}
