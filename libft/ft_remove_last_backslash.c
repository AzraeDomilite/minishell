/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_last_backslash.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:44:49 by baschnit          #+#    #+#             */
/*   Updated: 2024/12/11 01:35:48 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_remove_last_backslash(char *line)
{
	char	*i;

	i = line;
	while (*i)
		i++;
	if (i == line)
		return (line);
	i--;
	if (*i == '\\')
		*i = '\0';
	return (line);
}
