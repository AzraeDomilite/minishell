/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:14:15 by blucken           #+#    #+#             */
/*   Updated: 2025/05/05 11:57:39 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>

#include "cmd.h"
#include "libft.h"
#include "debug.h"
#include "shell.h"
#include "history.h"

#define BUF_SIZE 65536

void	ft_historyaddback(t_history *history, t_history *new)
{
	while (history->next)
		history = history->next;
	history->next = new;
}

/**
 * @brief 
 * 
 * @param history 
 * @return size_t 
 */
size_t	ft_historysize(t_history *history)
{
	size_t	size;

	size = 0;
	while (history)
	{
		size++;
		history = history->next;
	}
	return (size);
}

size_t	find_index_size(size_t index)
{
	size_t	size;

	size = 0;
	while (index)
	{
		size++;
		index = index / 10;
	}
	return (size);
}

size_t	count_file_lines(const char *filename)
{
	int		fd;
	char	buf[BUF_SIZE];
	size_t	count;
	ssize_t	bytes;
	ssize_t	i;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	bytes = read(fd, buf, BUF_SIZE);
	while (bytes > 0)
	{
		i = 0;
		while (i < bytes)
		{
			if (buf[i] == '\n')
				count++;
			i++;
		}
		bytes = read(fd, buf, BUF_SIZE);
	}
	close(fd);
	return (count);
}

/**
 * @brief Updates shell history from existing history file
 * @param shell Pointer to the shell structure
 * @details Reads the history file in chunks and processes each line to update
 * the shell's command history. If the file cannot be opened, silently returns.
 */
void	old_history_update(t_shell *shell)
{
	int		fd;
	char	buf[BUF_SIZE];
	ssize_t	bytes;

	if (!shell)
		return ;
	fd = open("tmp/.minishell_history", O_RDONLY);
	if (fd < 0)
		return ;
	bytes = read(fd, buf, BUF_SIZE);
	while (bytes > 0)
	{
		process_history_buffer(shell, buf, bytes);
		bytes = read(fd, buf, BUF_SIZE);
	}
	close(fd);
}
