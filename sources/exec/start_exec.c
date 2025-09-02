/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:20:06 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/02 17:18:11 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"
#include "utils.h"

void	start_exec(t_input *input)
{
	t_exec	*exec;

	exec = NULL;
	setup_signals_command();
	if (!init_exec(&exec, input))
		exit_minishell(input, NULL, EXIT_FAILURE);
	if (!set_blocks(exec, input))
	{
		wait_child(exec, &input->last_exit_status);
		exit_minishell(input, exec, 1);
	}
	wait_child(exec, &input->last_exit_status);
	setup_signals_interactive();
	free_and_close_exec(input, exec);
}
