/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:06:35 by baschnit          #+#    #+#             */
/*   Updated: 2024/11/24 01:00:04 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <inttypes.h>

#include "debug.h"

void	stop_time(char *msg, int break_point, int reset_stop)
{
	static int		stop[MAX_NUMBER_BREAKPOINTS];
	int				delta;
	struct timespec	tms;
	int				i;

	if (reset_stop)
		stop[break_point] = 0;
	clock_gettime(CLOCK_REALTIME, &tms);
	delta = tms.tv_sec % 10 * 1000000 + tms.tv_nsec / 1000;
	i = 0;
	while (i < (NUMBER_MUTED))
	{
		if (break_point == MUTED_BREAKPOINTS[i])
		{
			stop[break_point] = delta;
			return ;
		}
		i++;
	}
	if (stop[break_point] == 0)
		ft_printf("%i %s\n", (int) 0, msg);
	else
		ft_printf("%i %s\n", delta - stop[break_point], msg);
	stop[break_point] = delta;
}
