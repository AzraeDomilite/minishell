/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:06:42 by baschnit          #+#    #+#             */
/*   Updated: 2025/02/10 14:10:05 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tokens.h"
#include "debug.h"

void	print_tokens(t_tokens *tokens)
{
	char	*total;
	char	*temp;

	total = ft_strdup("");
	while (tokens)
	{
		temp = total;
		total = ft_strjoin(total, tokens->token);
		free(temp);
		if (tokens->next)
		{
			temp = total;
			total = ft_strjoin(total, ", ");
			free(temp);
		}
		tokens = tokens->next;
	}
	printf_debug("%s\n", total);
	free(total);
}
