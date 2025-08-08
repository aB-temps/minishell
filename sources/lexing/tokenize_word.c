/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:17:08 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/08 14:09:48 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include <stdio.h>

void	tokenize_word(t_input *input, size_t *i, char *line)
{
	char	*raw_content;
	size_t	j;
	enum e_bool	to_link;

	j = *i;
	to_link = FALSE;
	while (line[*i] && !is_whitespace(line[*i]) && !is_operator(line[*i])
		&& !is_quote(line[*i]))
		(*i)++;
	raw_content = ft_strndup(&line[j], *i - j);
	if (!raw_content)
		exit_parsing(input, EXIT_FAILURE);
	if (is_quote(line[*i]))
		to_link = TRUE;
	create_token(input, ARG, raw_content, to_link);
	input->token_qty++;
}
