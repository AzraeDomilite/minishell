/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:31:47 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 19:02:23 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

/**
 * @enum	e_mtype @brief types for pipe modifiers
 *
*/
typedef enum e_mtype
{
	NONE,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
	HEREDOC
}	t_mtype;

/**
 * @brief	holds type of modifier and its argument
 *
 * The argument will be the delimiter for heredoc or the filename otherwise
 *
 * 1. << delimiter	ask user for heredoc input until *delimiter* or ctrl + D
 * 2. < filename	replace STDIN with contents of *filename*
 * 3. >  filename write STDOUT into *filename*
 * 4. >> filename		append STDOUT into *filename*
 *
*/
typedef struct s_mod
{
	t_mtype	type;
	char	*arg;
}	t_mod;

/**
 * @brief	a list of modifiers
 *
 * minishell will use this structure to parse and store the mods for STDIN and
 * the ones for STDOUT. In bash only the last modifier in the command line will
 * actually be bound to STDIN or STDOUT.
 *
*/
typedef struct s_mods
{
	t_mod			*mod;
	struct s_mods	*next;
}	t_mods;

/**
 * @brief	holds a list of the arguments supplied on a command line
 *
*/
typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}	t_args;

/**
 * @brief	will hold the cmd name, its arguments and all pipe modifiers of a
 * 			command line without pipes
 *
 * example: < file1 < file2 cat << EOF >> file3 > file4 file5 file6
 *
*/
typedef struct s_cmd
{
	char	*name;
	char	*cmd_path;
	t_args	*args;
}	t_cmd;

int		parse_name_and_args(t_cmd *cmd, char *str);

#endif