/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:48 by enzo              #+#    #+#             */
/*   Updated: 2025/08/02 17:21:43 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"

static void	close_and_swap(t_exec *exec)
{
	if (exec->fd->fd1[0] != -1)
		close(exec->fd->fd1[0]);
	if (exec->fd->fd2[1] != -1)
		close(exec->fd->fd2[1]);
	exec->fd->fd1[0] = exec->fd->fd2[0];
	exec->fd->fd1[1] = exec->fd->fd2[1];
}

int	launch_all_commands(t_input *input, t_exec *exec, t_token *tokens_array)
{
	t_token	*cur_token;
	int		i;
	int		y;

	y = -1;
	i = 0;
	while (++y < input->token_qty && i < exec->cmd_count)
	{
		cur_token = &tokens_array[y];
		// create_files_no_cmd();
		if (cur_token->type == COMMAND)
		{
			if (pipe(exec->fd->fd2) == -1)
				exit_minishell(input, 1);
			exec->pid_child[i] = is_builtin(*cur_token, input, exec, i);
			if (exec->pid_child[i] == 0)
				exec->pid_child[i] = execute_command(cur_token, exec, i, input);
			if (i++ < exec->cmd_count - 1)
				close_and_swap(exec);
		}
	}
	close_all(exec);
	return (0);
}

void	wait_childs(t_exec *exec, t_input *input)
{
	int		i;
	t_token	*tokens_array;

	tokens_array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < exec->cmd_count)
		check_sig(exec, tokens_array, input, i++);
}
