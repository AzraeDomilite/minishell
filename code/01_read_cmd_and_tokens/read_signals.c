/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:54:25 by blucken           #+#    #+#             */
/*   Updated: 2025/05/04 17:43:00 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "libft.h"
#include "debug.h"

void	signal_handler_main(int signo)
{
	if (signo == SIGINT || SIGQUIT)
		write(STDOUT_FILENO, "\n", 1);
}

void	signal_handler_readline(int signo)
{
	if (signo == SIGINT)
	{
		print_debug("inside SIGINT handler fork %i\n");
		close(STDIN_FILENO);
	}
}

void	set_signals(void (*signal_handler)(int))
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &sa, NULL);
}

void	restore_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa, NULL);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGPIPE, &sa, NULL);
}
