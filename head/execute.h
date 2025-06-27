/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:28:23 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 18:28:28 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# ifndef DEBUG_EXECUTE_CMD
#  define DEBUG_EXECUTE_CMD 1
# endif

# ifndef DEBUG_MODIFIERS_CMD
#  define DEBUG_MODIFIERS_CMD 1
# endif

// typedef struct s_pid
// {
// 	pid_t			*pid;
// }	t_pid;

// typedef struct s_pids
// {
// 	t_pid			*pid;
// 	struct t_pids	*next;
// }	t_pids;

typedef struct s_qparser
{
	bool	in_dquote;
	bool	in_squote;
	int		read_pos;
	int		write_pos;
	char	*result;
}	t_qparser;

# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CMD_NOT_EXECUTABLE 126

// execute_cmd.c
pid_t	execute_cmd(t_node *node, int fd_in, int fd_out, t_shell *shell);
void	in_child(t_node *node, int fd_in, int fd_out, t_shell *shell);

// error_exec_handlers.c
pid_t	fork_error(void);
pid_t	args_tab_error(char *cmd_path, t_shell *shell);
void	dup2_error(char *cmd_path, t_shell *shell); //char **args_tabs, 

// execute_utils.c
char	*ft_strjoin_char(char *str, char c);
char	*ft_strend(char *str);
char	*ft_strjoin_null(char const *s1, char const *s2);
bool	builtin_change_sh_state(char *name);
void	check_access(t_cmd *cmd, char *cmd_path, t_shell *shell);
// execve_args_tab.c
char	**args_list_to_tab(t_cmd *cmd);

// modifiers.c
void	apply_modifiers(t_mods *mods, int *fd_in, int *fd_out);

// var_expansion.c

char	*replace_expand_var(char *old_str, t_shell *shell);
char	*expand_var(char *str, t_shell *shell);

// var_expansion_args.c
int		expand_vars(t_node *node, t_shell *shell);
char	*process_single_arg(char *arg, t_shell *shell);
char	*expand_var_heredoc(char *eof, char *line, t_shell *shell);
int		process_mods(t_mods *mods, t_shell *shell);
// var_expansion_utils.c
void	init_quotes_parser(t_qparser *p, char *arg);
void	handle_quotes(char c, t_qparser *p);
char	*handle_exit_status_qp(t_qparser *p, t_shell *shell);
int		get_var_length(char *arg, int start_pos);
void	handle_var_expansion(t_qparser *p, char *var_name, char *expanded);

pid_t	pipe_tree(t_ctree *tree, int fd_in, int fd_out, t_shell *shell);
pid_t	chain_tree(t_ctree *tree, int fd_in, int fd_out, t_shell *shell);

int		execute_tree(t_ctree *tree, int fd_in, int fd_out, t_shell *shell);
pid_t	execute_tree_no_wait(t_ctree *tree, int fd_in, int fd_out, \
t_shell *shell);
pid_t	fork_tree_no_wait(t_ctree *tree, int fd[2], t_shell *shell, \
t_mods *mods);
int		fork_tree(t_ctree *tree, int fd[2], t_shell *shell, t_mods *mods);

#endif