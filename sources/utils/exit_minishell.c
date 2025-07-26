/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:34 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 17:47:35 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "utils.h"

void	exit_minishell(t_input *input, int exit_code)
{
	if (input)
	{
		if (input->v_tokens)
			clear_vector(&input->v_tokens);
		if (input->env)
		{
			ft_lstclear(&input->env->list, &clear_env_list_elem);
			free_tab_return_null(input->env->array);
			free(input->env);
		}
		if (input->line)
			free(input->line);
		if (input->prompt)
			free(input->prompt);
		free(input);
	}
	exit(exit_code);
}
