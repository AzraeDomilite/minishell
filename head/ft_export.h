/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:25:57 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 19:17:44 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPORT_H
# define FT_EXPORT_H

// ft_export.c
int		ft_export(t_args *args, int fd_out, t_shell *shell);
char	**add_last_tab(char **tab, char *str);

// export_utils.c
char	*get_var_name(char *arg);
size_t	get_env_len(char **env);
size_t	get_var_pos(char **env, char *var_name);
int		print_env_export(int fd_out, t_shell *shell);

// var_management.c
char	**add_var(char *arg, char **env);
void	replace_var(char *arg, char **env);
void	replace_var(char *arg, char **env);
int		var_exist(char *arg, char **env);

#endif