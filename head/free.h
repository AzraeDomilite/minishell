/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:02:50 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 20:02:55 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "cmd.h"
# include "tree.h"
# include "shell.h"

//void	free_mod(t_mod *mod);
void	free_mod(t_mod *mod);
void	free_mods(t_mods **mods);
void	free_ctree(t_ctree **tree);
void	ft_free_tab(char **tab);
int		close_non_std_fd(int fd);
void	free_mods(t_mods **mods);
void	free_builtin(t_builtin *builtin);
void	free_pipes(t_plist **pipes);
void	free_buffer(t_shell *shell);
void	free_history(t_history *history);
void	free_shell(t_shell *shell);
void	free_on_exit(t_shell *shell, int ret);

#endif