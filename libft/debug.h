/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 03:34:52 by baschnit          #+#    #+#             */
/*   Updated: 2025/02/12 11:07:49 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# define CUSTOM_BREAKPOINT_ONE 1
# define CUSTOM_BREAKPOINT_TWO 2
# define CUSTOM_BREAKPOINT_THREE 3

# define MAX_NUMBER_BREAKPOINTS 20
# define NUMBER_MUTED 2

void	stop_time(char *msg, int break_point, int reset_stop);

# define DEBUG 1
//# define DEBUG_FILE 0
# define DEBUG_FILE "debug.log"

int		get_debug_fd(void);
void	print_debug(char *msg);
int		printf_debug(const char *format, ...);
int		close_debug_fd(void);

//# define MUTED_BREAKPOINTS (int[])
// {CUSTOM_BREAKPOINT_ONE, CUSTOM_BREAKPOINT_TWO}

#endif