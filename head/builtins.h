/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:35:04 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 17:35:04 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define EXIT_NUM_ARG		"minishell: exit: numeric argument required\n"
# define EXIT_TOO_MANY_ARGS	"minishell: exit: too many arguments\n"

# define EXIT_NUM_ARG		"minishell: exit: numeric argument required\n"
# define EXIT_TOO_MANY_ARGS	"minishell: exit: too many arguments\n"

# include "shell.h"

int			copy_fd_to_fd(int fd_in, int fd_out);
int			ft_env(t_args *args, int fd_out, t_shell *shell);
int			ft_echo(t_args *args, int fd_out, t_shell *shell);
int			ft_cd(t_args *args, int fd_out, t_shell *shell);
void		update_pwd_var(t_shell *shell);
int			ft_pwd(t_args *args, int fd_out, t_shell *shell);
int			ft_unset(t_args *args, int fd_out, t_shell *shell);
void		sort_env(char **env);
char		**add_last_tab(char **tab, char *str);
int			ft_exit(t_args *args, int fd_out, t_shell *shell);
t_builtin	*in_builtins(char *cmd, t_builtins *builtins);
bool		is_var_valid(char *arg);

#endif