/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:30 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/16 20:02:23 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "style.h"

void	create_token(t_input *input, int type, char *raw_content,
	enum e_bool to_link)
{
	t_token	temp_token;

	init_token(&temp_token);
	temp_token.type = type;
	if (!(type >= PIPE && type <= HEREDOC))
		temp_token.raw_content = raw_content;
	else
	{
		temp_token.raw_content = ft_strdup(raw_content);
		if (!temp_token.raw_content)
			exit_parsing(input, EXIT_FAILURE);
	}
	temp_token.link_to_next = to_link;
	if (!add_element(input->v_tokens, &temp_token))
	{
		if (!(type >= PIPE && type <= HEREDOC) && raw_content)
			free(raw_content);
		exit_parsing(input, EXIT_FAILURE);
	}
}
