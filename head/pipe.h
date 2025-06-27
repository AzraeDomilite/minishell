/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:30:50 by baschnit          #+#    #+#             */
/*   Updated: 2024/12/11 05:35:33 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

typedef struct s_pipe
{
	int	write;
	int	read;
}	t_pipe;

typedef struct s_plist
{
	t_pipe			*pipe;
	struct s_plist	*next;
}	t_plist;

t_pipe	*add_new_pipe(t_plist **list);
void	close_all_pipes_except(int fd, int fd2, t_plist *pipes);
void	close_all_pipes(t_plist *pipes);

#endif