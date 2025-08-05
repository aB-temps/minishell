/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_v_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:16 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/02 16:22:12 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "input.h"
#include "utils.h"

void	clear_token(t_token token)
{
	if (token.type == COMMAND)
		free_tab_return_null((char **)token.formatted_content);
	else if (token.type == HEREDOC && ft_strlen(token.raw_content) > 2)
	{
		safe_close(((int *)token.formatted_content)[0]);
		safe_close(((int *)token.formatted_content)[1]);
		free(token.formatted_content);
	}
	else
		free(token.formatted_content);
	free(token.raw_content);
}

void	clear_v_token(t_vector *tokens)
{
	const t_token	*array = (t_token *)tokens->array;
	size_t			i;

	i = 0;
	while (i < tokens->nb_elements)
	{
		clear_token(array[i]);
		i++;
	}
}
