/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:52:46 by blucken           #+#    #+#             */
/*   Updated: 2025/02/14 13:23:05 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "pipe.h"
#include "libft.h"
#include "debug.h"

t_pipe	*add_new_pipe(t_plist **list)
{
	t_pipe	*ppipe;
	t_plist	*plist;
	int		pipe_fds[2];

	if (!set(&ppipe, malloc(sizeof(t_pipe))))
		return (NULL);
	if (!set(&plist, ft_lstnew(ppipe)))
		return (free(ppipe), NULL);
	if (pipe(pipe_fds) == (-1))
		return (free(plist), free(ppipe), NULL);
	ppipe->read = pipe_fds[0];
	ppipe->write = pipe_fds[1];
	printf_debug("created new pipe with write %i and read %i\n", \
		pipe_fds[1], pipe_fds[0]);
	ft_lstadd_back((t_list **) list, (t_list *) plist);
	return (ppipe);
}

void	close_all_pipes(t_plist *pipes)
{
	while (pipes)
	{
		if (pipes->pipe->read != STDIN_FILENO && pipes->pipe->read != \
			STDOUT_FILENO && pipes->pipe->read != STDERR_FILENO)
			close(pipes->pipe->read);
		if (pipes->pipe->write != STDIN_FILENO && pipes->pipe->write != \
			STDOUT_FILENO && pipes->pipe->write != STDERR_FILENO)
			close(pipes->pipe->write);
		pipes = pipes->next;
	}
}

void	close_all_pipes_except(int fd, int fd2, t_plist *pipes)
{
	while (pipes)
	{
		if (pipes->pipe->read != fd && pipes->pipe->read != fd2)
			if (pipes->pipe->read != STDIN_FILENO && pipes->pipe->read != \
				STDOUT_FILENO && pipes->pipe->read != STDERR_FILENO)
				close(pipes->pipe->read);
		if (pipes->pipe->write != fd && pipes->pipe->write != fd2)
			if (pipes->pipe->write != STDIN_FILENO && pipes->pipe->write != \
				STDOUT_FILENO && pipes->pipe->write != STDERR_FILENO)
				close(pipes->pipe->write);
		pipes = pipes->next;
	}
}
