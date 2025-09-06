/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:12:28 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/04 01:41:12 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checking.h"
#include "input.h"
#include "style.h"

enum e_bool	check_syntax_error(t_input *input)
{
	const t_token	*array = (t_token *)input->v_tokens->array;
	ssize_t			i;

	i = 0;
	if (array[0].type == PIPE || (array[input->token_qty - 1].type >= PIPE
			&& array[input->token_qty - 1].type <= HEREDOC))
		return (FALSE);
	while (i < input->token_qty)
	{
		if (i + 1 < input->token_qty && (array[i].type > PIPE
				&& array[i].type <= HEREDOC) && array[i + 1].type < ARG)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	print_syntax_error(t_input *input)
{
	ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
	input->last_exit_status = 2;
}
