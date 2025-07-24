/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:50 by enzo              #+#    #+#             */
/*   Updated: 2025/07/24 15:57:42 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include <stdio.h>

int	free_child(t_exec *exec, t_input *input)
{
	close_all(exec);
	free(exec->fd);
	free(exec->cmd_path);
	free(exec->pid_child);
	clear_vector(&input->v_tokens);
	ft_lstclear(&input->env->list, &clear_env_list_elem);
	free_tab_return_null(input->env->array);
	free(input->env);
	free(input->prompt);
	free(input);
	return (127);
}

static int	execute_child(t_exec *exec, int i, t_input *input)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free(exec->cmd_path);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		prepare_pipe(exec, i);
		if (!exec->cmd_path)
			exit(free_child(exec, input));
		execve(exec->cmd_path, exec->args, input->env->array);
		exit(free_child(exec, input));
	}
	free(exec->cmd_path);
	return (pid);
}

int	execute_command(t_token *current_token, t_exec *exec, int i, t_input *input)
{
	int	pid;

	pid = 0;
	exec->args = (char **)(current_token->formatted_content);
	exec->cmd_path = find_full_command_path(exec->args[0], input->env->array);
	pid = execute_child(exec, i, input);
	return (pid);
}
