/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:45 by enzo              #+#    #+#             */
/*   Updated: 2025/07/29 23:20:48 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include <errno.h>

int	execute_all_commands(t_input *input, t_exec *exec)
{
	t_token	*tokens_array;
	int		res;
	int		saved_exit_status;
	char	**cmd;

	exec->pid_child = ft_calloc(exec->cmd_count, sizeof(pid_t));
	if (!exec->pid_child)
		return (1);
	tokens_array = (t_token *)input->v_tokens->array;
	res = create_all_files(exec, input, tokens_array);
	if (res != 0)
		return (res);
	res = launch_all_commands(input, exec);
	if (res != 0)
		return (res);
	saved_exit_status = input->last_exit_status;
	wait_childs(exec, input);
	if (exec->cmd_count == 1 && tokens_array[0].type == COMMAND)
	{
		cmd = (char **)tokens_array[0].formatted_content;
		if (cmd && check_builtin(cmd[0]) == 1)
			input->last_exit_status = saved_exit_status;
	}
	free(exec->pid_child);
	return (0);
}

static int	init_t_exec(t_exec *exec, t_input *input)
{
	exec->cmd_path = NULL;
	exec->args = NULL;
	exec->cmd_count = count_cmd(input);
	exec->fd_infile = -1;
	exec->fd_outfile = -1;
	exec->pid_child = NULL;
	exec->fd = ft_calloc(1, sizeof(t_fd));
	if (!exec->fd)
		return (-1);
	exec->fd->fd1[0] = -1;
	exec->fd->fd1[1] = -1;
	exec->fd->fd2[0] = -1;
	exec->fd->fd2[1] = -1;
	return (0);
}

void	start_exec(t_input *input)
{
	t_exec	exec;
	int		res;

	if (init_t_exec(&exec, input) == -1)
		return (1);
	res = execute_all_commands(input, &exec);
	free(exec.fd);
	if (res == 1)
		exit_minishell(input, input->last_exit_status);
}
