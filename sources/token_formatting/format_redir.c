/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:24:13 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/08 12:31:49 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_formatting.h"

static char	*unquote_arg(char *qtd_arg)
{
	size_t	i;

	i = 0;
	if (!ft_strchr(qtd_arg, '\'') && !ft_strchr(qtd_arg, '"'))
		return (ft_strdup(qtd_arg));
	while (!is_quote(qtd_arg[i]))
		i++;
	if (qtd_arg[i] == '\'')
		return (str_patdel(qtd_arg, "\'"));
	else if (qtd_arg[i] == '\"')
		return (str_patdel(qtd_arg, "\""));
	return (ft_strdup(qtd_arg));
}

static char	*join_unquoted_args(t_token *array, size_t i, size_t *j,
		bool *expand)
{
	char	*content;

	content = ft_strdup(array[i].raw_content);
	if (!content)
		return ((void *)0);
	if (ft_strchr(content, '\'') || ft_strchr(content, '"'))
	{
		*expand = false;
		content = str_replace(&content, unquote_arg(content));
	}
	while (content && array[i].link_to_next)
	{
		content = str_free_to_join(content, array[i + 1].raw_content);
		if (!content)
			return ((void *)0);
		if (content && (ft_strchr(content, '\'') || ft_strchr(content, '"')))
		{
			*expand = false;
			content = str_replace(&content, unquote_arg(content));
		}
		i++;
		(*j)++;
	}
	return (content);
}

static void	tag_tokens_to_remove(t_token *array, ssize_t *i, size_t j)
{
	while (j > 0)
	{
		array[++(*i)].type = -1;
		j--;
	}
}

void	format_redir(t_input *input, ssize_t *i)
{
	t_token		*array;
	bool	expand;
	size_t		j;

	array = (t_token *)input->v_tokens->array;
	expand = false;
	if (array[*i].type == HEREDOC)
		expand = true;
	j = 0;
	array[(*i) + 1].raw_content = str_replace(&array[*i + 1].raw_content,
			join_unquoted_args(array, *i + 1, &j, &expand));
	if (!array[(*i) + 1].raw_content)
		exit_parsing(input, EXIT_FAILURE);
	array[*i].link_to_next = expand;
	if (*i + 1 < input->token_qty && array[*i + 1].type == ENV_VAR)
		array[*i].formatted_content
			= str_replace((char **)&array[*i].formatted_content,
				ft_strdup(array[*i + 1].formatted_content));
	else if (*i + 1 < input->token_qty && array[*i + 1].type >= ARG)
		array[*i].formatted_content
			= str_replace((char **)&array[*i].formatted_content,
				ft_strdup(array[*i + 1].raw_content));
	if (!array[*i].formatted_content)
		exit_parsing(input, EXIT_FAILURE);
	tag_tokens_to_remove(array, i, ++j);
}
