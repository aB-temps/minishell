/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:50 by enzo              #+#    #+#             */
/*   Updated: 2025/08/02 14:13:03 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include "utils.h"
#include <stdio.h>
#include <sys/stat.h>

void	close_hd_fd(t_input *input)
{
	t_token	*tokens_array;
	t_token	*current_token;
	int		hd_fd;
	int		i;

	i = 0;
	tokens_array = input->v_tokens->array;
	while (i < input->token_qty)
	{
		current_token = &tokens_array[i];
		if (current_token->type == HEREDOC)
		{
			hd_fd = ((int *)current_token->formatted_content)[1];
			if (hd_fd)
				close(hd_fd);
		}
		i++;
	}
}

void	reset_sig(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

static int	execute_child(t_exec *exec, int i, t_input *input, int error)
{
	pid_t	pid;
	int		res;

	pid = fork();
	if (pid == -1)
	{
		free(exec->cmd_path);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		res = create_all_files(exec, input, i);
		if (res != 0)
			exit_minishell(input, exec, error);
		reset_sig();
		prepare_pipe(exec, i);
		if (!exec->cmd_path)
			exit_minishell(input, exec, error);
		execve(exec->cmd_path, exec->args, input->env->array);
		exit_minishell(input, exec, error);
	}
	free(exec->cmd_path);
	exec->cmd_path = NULL;
	return (pid);
}

int	execute_command(t_token *current_token, t_exec *exec, int i, t_input *input)
{
	int	pid;
	int	error;
	int	res;

	res = 0;
	error = 0;
	pid = 0;
	exec->args = (char **)(current_token->formatted_content);
	exec->cmd_path = find_full_command_path(&exec->args[0], input->env->array,
			&error);
	if (exec->cmd_path && ft_strchr(exec->cmd_path, '/'))
	{
		res = check_if_dir(input, exec->cmd_path);
		if (res != 1 && res != 0)
			exit_minishell(input, exec, EXIT_FAILURE);
	}
	pid = execute_child(exec, i, input, error);
	close_hd_fd(input);
	return (pid);
}
