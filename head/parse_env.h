/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:09:25 by blucken           #+#    #+#             */
/*   Updated: 2025/05/03 19:04:14 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ENV_H
# define PARSE_ENV_H

# include "shell.h"
# include "cmd.h"
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <stdlib.h>

# ifndef DEBUG_PARSE_ENV
#  define DEBUG_PARSE_ENV 0
# endif

char	*get_cmd_path(char *name, t_shell *shell);

/**
 * @brief			Retrieves the value of an environment variable
 *
 * @param env		The environment variables array
 * @param var_name	The name of the variable to retrieve
 * @return			char* The value of the variable, or NULL if not found
*/
char	*get_env_value(char **env, const char *var_name);

#endif