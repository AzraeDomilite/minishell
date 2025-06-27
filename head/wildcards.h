/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:28:27 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 18:59:17 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

typedef struct s_match_array
{
	char	**matches;
	int		count;
	int		capacity;
}	t_match_array;

t_args			*expand_wildcards_list(t_args *args, char *expanded);
t_args			*process_wildcards(t_args *args, char *expanded);

void			ft_sort_matches(t_match_array *array);
void			ft_free_match_array(t_match_array *array);
t_match_array	*ft_init_match_array(void);
bool			ft_match_star(const char *pattern, const char *filename);
bool			ft_matches_pattern(const char *pattern, const char *filename);

char			*expand_cmd_wildcards(char *cmd);
void			ft_add_match(t_match_array *array, const char *match);
#endif