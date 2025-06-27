/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isblank.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:52:40 by baschnit          #+#    #+#             */
/*   Updated: 2024/12/06 23:37:14 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief checks if a character is space or tab
 * 
 * @param c 
 * @return int 
 */
int	ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}
