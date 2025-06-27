/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:14:51 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 18:53:12 by baschnit         ###   ########.fr       */
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

#ifndef DEBUG_HISTORY
# define DEBUG_HISTORY 1
#endif

#ifndef ID_WIDTH
# define ID_WIDTH 5
#endif

static void	write_history_line(int fd_out, char *number, char *line);
static int	no_history(int fd_out);

/**
 * @brief Manages the shell command history
 * @details Adds a new command to both the readline history and updates
 * 			the shell's internal history storage. This function ensures
 * 			command history persistence and proper memory management.
 * 
 * @param shell Pointer to the shell structure containing history data
 * @param line The command line string to add to history
 * @return bool Returns true if history was successfully updated,
 * false otherwise
 * @note Returns false if either shell or line parameters are NULL
 */
bool	manage_history(t_shell *shell, char *line)
{
	if (!line)
		return (true);
	return (update_history(shell, line));
}

/**
 * @brief Display command history
 * @details Safely prints the shell command history to the specified file 
 *          descriptor. Each history entry is formatted with a line number
 * 			and the command text. The function handles empty history
 * 			and invalid memory accesses gracefully.
 *
 * @param args Command arguments (unused in this function)
 * @param fd_out File descriptor where the history output will be written
 * @param shell Pointer to shell structure containing the history linked list
 * @return int Returns 0 on successful execution, 1 on failure
 * (memory allocation error or NULL shell)
 * @note Prints "No history" if shell is NULL or history is empty
 */
int	ft_history(t_args *args, int fd_out, t_shell *shell)
{
	t_history	*current;
	char		*number;
	int			i;

	(void)args;
	if (!shell || !shell->history)
		return (no_history(fd_out));
	current = shell->history;
	i = 1;
	while (current)
	{
		if (!current->line)
		{
			current = current->next;
			continue ;
		}
		number = ft_itoa(i++);
		if (!number)
			return (1);
		write_history_line(fd_out, number, current->line);
		current = current->next;
	}
	return (0);
}

static int	no_history(int fd_out)
{
	write(fd_out, "No history\n", 11);
	return (1);
}

/**
 * @brief Writes a single history entry to the specified file descriptor
 * @details Formats and outputs a single history entry with proper spacing
 *          and numbering. The format is: "  number  command\n"
 *
 * @param fd_out File descriptor where the line will be written
 * @param number String representation of the history entry number,
 * freed at the end
 * @param line The command line text to be displayed
 * @note This is a helper function for ft_history, also free number
 */
static void	write_history_line(int fd_out, char *number, char *line)
{
	write(fd_out, "     ", 5 - ft_strlen(number));
	write(fd_out, number, ft_strlen(number));
	write(fd_out, "  ", 2);
	write(fd_out, line, ft_strlen(line));
	write(fd_out, "\n", 1);
	free(number);
}
