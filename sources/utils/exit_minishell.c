/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:34 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/20 02:04:44 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include "utils.h"
#include <readline/readline.h>

void	close_all_hd(t_input *input)
{
	t_list	*current;

	current = input->stash;
	while (current)
	{
		if (current->content)
			safe_close(*(int *)current->content);
		current = current->next;
	}
}

void	exit_minishell(t_input *input, t_exec *exec, int exit_code)
{

	free_and_close_exec(input, exec);
	exit_parsing(input, exit_code);
}

void	exit_parsing(t_input *input, int exit_code)
{
	if (input)
	{
		if (input->stash)
			close_all_hd(input);
		if (input->v_tokens)
			clear_vector(&input->v_tokens);
		if (input->stash)
			ft_lstclear(&input->stash, &free);
		if (input->env)
		{
			if (input->env->list)
				ft_lstclear(&input->env->list, &clear_env_list_elem);
			if (input->env->array)
				free_tab_return_null(input->env->array);
			free(input->env);
		}
		if (input->line)
			free(input->line);
		if (input->prompt)
			free(input->prompt);
		free(input);
	}
	rl_clear_history();
	exit(exit_code);
}
