/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_v_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:59:09 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/01 20:42:45 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "utils.h"

void	clear_token(t_token *token)
{
	if (token)
	{
		if (token->formatted_content)
		{
			if (token->type == COMMAND)
				free_tab_return_null((char **)token->formatted_content);
			else if (token->type == HEREDOC
				&& ft_strlen(token->raw_content) > 2)
			{
				safe_close(&((int *)token->formatted_content)[0]);
				safe_close(&((int *)token->formatted_content)[1]);
				free(token->formatted_content);
			}
			else
				free(token->formatted_content);
			token->formatted_content = (void *)0;
		}
		if (token->raw_content)
		{
			free(token->raw_content);
			token->raw_content = (void *)0;
		}
	}
}

void	clear_v_token(t_vector *tokens)
{
	const t_token	*array = (t_token *)tokens->array;
	size_t			i;

	i = 0;
	while (i < tokens->nb_elements)
	{
		clear_token((t_token *)&array[i]);
		i++;
	}
}
