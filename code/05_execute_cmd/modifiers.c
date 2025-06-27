/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:01:43 by blucken           #+#    #+#             */
/*   Updated: 2025/04/28 17:02:26 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "cmd.h"
#include "shell.h"
#include "libft.h"
#include "debug.h"
#include "parse_env.h"
#include "free.h"
#include "execute.h"
#include "libft.h"

static void	handle_infile(const char *filename, int *fd_in);
static void	handle_outfile(const char *filename, int *fd_out, int append_mode);
static void	handle_heredoc(const char *content, int *fd_in);
static bool	check_infile_access(const char *filename, int *fd_in);

/**
 * @brief Applies input/output modifiers to a command
 * @param mods Linked list of modifiers to apply
 * @param fd_in Pointer to input file descriptor
 * @param fd_out Pointer to output file descriptor
 */
void	apply_modifiers(t_mods *mods, int *fd_in, int *fd_out)
{
	while (mods)
	{
		if (mods->mod->type == INFILE)
			handle_infile(mods->mod->arg, fd_in);
		else if (mods->mod->type == OUTFILE)
			handle_outfile(mods->mod->arg, fd_out, 0);
		else if (mods->mod->type == OUTFILE_APPEND)
			handle_outfile(mods->mod->arg, fd_out, 1);
		else if (mods->mod->type == HEREDOC)
			handle_heredoc(mods->mod->arg, fd_in);
		if (DEBUG_MODIFIERS_CMD && mods->mod->type == OUTFILE)
			print_debug("MOD IS OUTFILE");
		mods = mods->next;
	}
}

/**
 * @brief Handles input file redirection
 * @details Reads content from the specified file and creates a pipe to redirect
 *          the content as input for the command.
 * @param filename Path to the input file
 * @param fd_in Pointer to the input file descriptor to be modified
 */
static void	handle_infile(const char *filename, int *fd_in)
{
	int		fds[2];
	int		fd;
	char	*line;

	if (!check_infile_access(filename, fd_in))
		return ;
	pipe(fds);
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		write(fds[1], line, ft_strlen(line));
		line = get_next_line(fd);
	}
	close(fd);
	close(fds[1]);
	close_non_std_fd(*fd_in);
	*fd_in = fds[0];
}

static bool	check_infile_access(const char *filename, int *fd_in)
{
	if (access(filename, F_OK) == -1)
	{
		if (*fd_in == -1)
			return (false);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd((char *)filename, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		*fd_in = -1;
		return (false);
	}
	if (access(filename, R_OK) == -1)
	{
		if (*fd_in == -1)
			return (false);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd((char *)filename, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		*fd_in = -1;
		return (false);
	}
	return (true);
}

/**
 * @brief Handles output file redirection
 * @param filename Path to the output file
 * @param fd_out Pointer to the output file descriptor
 * @param append_mode If true, opens file in append mode
 */
static void	handle_outfile(const char *filename, int *fd_out, int append_mode)
{
	mode_t	mode;

	mode = 0644;
	close_non_std_fd(*fd_out);
	if (DEBUG_MODIFIERS_CMD)
		printf_debug("open : %s\n", filename);
	if (append_mode)
		*fd_out = open(filename, O_CREAT | O_APPEND | O_WRONLY, mode);
	else
		*fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
	if (*fd_out == -1)
	{
		write(STDERR_FILENO, "minishell : ", 12);
		perror(filename);
	}
}

/**
 * @brief Handles heredoc input redirection
 * @param content String containing heredoc content
 * @param fd_in Pointer to input file descriptor
 */
static void	handle_heredoc(const char *content, int *fd_in)
{
	int	fds[2];

	pipe(fds);
	write(fds[1], content, ft_strlen(content));
	close(fds[1]);
	close_non_std_fd(*fd_in);
	*fd_in = fds[0];
}
