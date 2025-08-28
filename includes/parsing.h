/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:33 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/28 17:40:04 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "lexing.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>

void	get_input(char **env, char **av);
void	*parse_input(t_input *input);

#endif
