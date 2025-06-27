/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cancel_newline_at_end.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:59:14 by baschnit          #+#    #+#             */
/*   Updated: 2024/12/07 00:30:40 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief replaces newline or carriage return + newline at end with \0
 * 
 * @param line string of which newline at the end will be replaced
 */
void	ft_cancel_newline_at_end(char *line)
{
	char	*i;

	i = line;
	while (*i)
		i++;
	if (i == line)
		return ;
	i--;
	if (*i == '\n')
		*i = '\0';
	if (i == line)
		return ;
	i--;
	if (*i == '\r')
		*i = '\0';
}
