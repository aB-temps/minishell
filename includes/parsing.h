/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:33 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/27 19:43:34 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "lexing.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>

void	get_input(char **env);
void	*parse_input(t_input *input);
void	format_input(t_input *input, t_token *array);

#endif
