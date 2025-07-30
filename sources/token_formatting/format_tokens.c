/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:24:05 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/30 19:00:05 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "token_formatting.h"

static void	handle_env_var_expansion(t_input *input)
{
	t_token	*array;
	int		last_type;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	last_type = -1;
	i = 0;
	while (i < input->token_qty)
	{
		if (array[i].type < ARG)
			last_type = array[i].type;
		if (array[i].type != S_QUOTES && ft_strchr(array[i].raw_content, '$')
			&& ft_strlen(array[i].raw_content) != 1 && last_type != HEREDOC)
		{
			array[i].formatted_content = substitute_env_var(array[i].raw_content,
					input);
			if (!array[i].formatted_content)
				exit_minishell(input, EXIT_FAILURE);
			array[i].type = ENV_VAR;
		}
		i++;
	}
}

static void	handle_quotes(t_token *array, t_input *input)
{
	char	*temp;
	ssize_t	i;
	int		last_type;

	i = 0;
	last_type = 0;
	while (i < input->token_qty)
	{
		temp = array[i].raw_content;
		if (array[i].type < ARG)
			last_type = array[i].type;
		if (array[i].type == S_QUOTES && !(i - 1 >= 0 && last_type == HEREDOC))
		{
			array[i].raw_content = str_patdel(array[i].raw_content, "'");
			free(temp);
		}
		else if (array[i].type == D_QUOTES && !(i - 1 >= 0
				&& last_type == HEREDOC))
		{
			array[i].raw_content = str_patdel(array[i].raw_content, "\"");
			free(temp);
		}
		i++;
	}
}

void	format_tokens(t_input *input)
{
	t_token	*array;
	ssize_t	i;
	ssize_t	last_type;

	i = 0;
	last_type = -1;
	array = (t_token *)input->v_tokens->array;
	handle_quotes(array, input);
	handle_env_var_expansion(input);
	remove_empty_env_var(input, array);
	array = (t_token *)input->v_tokens->array;
	print_input(input, "AFTER REM USELESS VAR");
	while (i < input->token_qty)
	{
		if (array[i].type >= REDIR_IN && array[i].type <= HEREDOC)
			format_redir(input, &i);
		else
			i++;
	}
	remove_useless_token(input, array);
	array = (t_token *)input->v_tokens->array;
	print_input(input, "AFTER FORMAT REDIR");
	i = 0;
	while (i < input->token_qty)
	{
		if (array[i].type >= ARG && !(last_type >= REDIR_IN
				&& last_type <= HEREDOC))
			format_command(input, array, &i);
		else
			i++;
		if (i > 1)
			last_type = array[i - 1].type;
	}
	print_input(input, "AFTER FORMAT CMD");
}
