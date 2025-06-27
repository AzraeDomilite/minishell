/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2004/05/20 16:45:14 by blucken           #+#    #+#             */
/*   Updated: 2025/05/05 11:43:50 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "debug.h"
#include "libft.h"

int	get_debug_fd(void)
{
	static int	fd;
	char		*file;
	char		*pwd;
	mode_t		mode;

	mode = 0644;
	if (fd == 0)
	{
		if (!DEBUG_FILE)
			fd = STDOUT_FILENO;
		else
		{
			file = getcwd(NULL, 0);
			pwd = ft_strnstr(file, "test_case", ft_strlen(file));
			free(file);
			if (pwd)
				file = ft_strjoin("../", DEBUG_FILE);
			else
				file = ft_strdup(DEBUG_FILE);
			unlink(file);
			fd = open(file, O_CREAT | O_WRONLY, mode);
			free(file);
		}
	}
	return (fd);
}

int	close_debug_fd(void)
{
	int		fd;
	mode_t	permissions;

	permissions = S_IRWXU | S_IRWXG | S_IRWXO;
	chmod(DEBUG_FILE, permissions);
	fd = get_debug_fd();
	if (fd != STDOUT_FILENO && fd != STDIN_FILENO && fd != STDERR_FILENO)
		return (close(fd));
	return (1);
}

void	print_debug(char *msg)
{
	int	fd;

	fd = get_debug_fd();
	ft_dprintf(fd, "--%i-- %s\n", getpid(), msg);
}

int	printf_debug(const char *format, ...)
{
	va_list	args;
	int		ret;
	int		fd;

	usleep(5e4);
	fd = get_debug_fd();
	ret = ft_dprintf(fd, "--%i-- ", getpid());
	va_start(args, format);
	ret += ft_vdprintf(fd, format, args);
	va_end(args);
	return (ret);
}
