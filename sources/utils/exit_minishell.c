/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:34 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/02 17:45:49 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include "utils.h"

void	exit_minishell(t_input *input, t_exec *exec, int exit_code)
{
	close_hd_fd(input);
	if (exec)
	{
		close_all(exec);
		if (exec->fd)
			free(exec->fd);
		if (exec->cmd_path)
			free(exec->cmd_path);
		if (exec->pid_child)
			free(exec->pid_child);
	}
	exit_parsing(input, exit_code);
}

void	exit_parsing(t_input *input, int exit_code)
{
	if (input)
	{
		if (input->v_tokens)
			clear_vector(&input->v_tokens);
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
	exit(exit_code);
}
