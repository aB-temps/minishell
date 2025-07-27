/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:34 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/27 19:46:52 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "checking.h"

void	tokenize_input(t_input *input, char *line);
void	tokenize_word(t_input *input, size_t *i, char *line);
void	tokenize_operator(t_input *input, size_t *i, char *line,
			size_t line_len);
void	*tokenize_quote(t_input *input, size_t *i, char *line);

#endif
