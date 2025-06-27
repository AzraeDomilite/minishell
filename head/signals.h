/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:40:24 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 19:00:23 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	signal_handler_main(int signo);
void	signal_handler_readline(int signo);
void	set_signals(void (*signal_handler)(int));
void	restore_signals(void);

#endif