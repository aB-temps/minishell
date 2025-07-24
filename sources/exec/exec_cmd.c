/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:45 by enzo              #+#    #+#             */
/*   Updated: 2025/07/24 11:41:02 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include <errno.h>

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static int	execute_all_commands(t_input *input, t_exec *exec)
{
	t_token	*tokens_array;

	exec->cmd_count = count_cmd(input);
	exec->pid_child = ft_calloc(exec->cmd_count, sizeof(pid_t));
	if (!exec->pid_child)
		return (1);
	tokens_array = (t_token *)input->v_tokens->array;
	if (create_all_files(exec, tokens_array, input->token_qty)
		|| launch_all_commands(input, exec))
		return (1);
	print_exec(exec, "AFTER_EXEC");
	wait_childs(exec, input);
	free(exec->pid_child);
	return (0);
}

int	handle_redir_in(t_exec *exec, t_token current_token)
{
	int	fd_temp;

	if (current_token.formatted_content)
	{
		fd_temp = open(current_token.formatted_content, O_RDONLY);
		if (fd_temp == -1)
		{
			perror(current_token.formatted_content);
			return (1);
		}
		else
		{
			if (exec->fd_infile != -1)
				close(exec->fd_infile);
			exec->fd_infile = fd_temp;
		}
	}
	return (0);
}

int	handle_redir_out(t_exec *exec, t_token current_token)
{
	int	flags;
	int	fd_temp;

	if (current_token.type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd_temp = open(current_token.formatted_content, flags, 0644);
	if (fd_temp == -1)
	{
		perror(current_token.formatted_content);
		return (1);
	}
	else
	{
		if (exec->fd_outfile != -1)
			close(exec->fd_outfile);
		exec->fd_outfile = fd_temp;
	}
	return (0);
}

int	create_all_files(t_exec *exec, t_token *token_array, int token_qty)
{
	int	i;

	i = 0;
	while (i < token_qty)
	{
		if (token_array[i].type == APPEND || token_array[i].type == REDIR_OUT)
		{
			if (handle_redir_out(exec, token_array[i]))
				return (1);
		}
		else if (token_array[i].type == REDIR_IN)
		{
			if (handle_redir_in(exec, token_array[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

void	init_t_exec(t_exec *exec)
{
	exec->cmd_path = NULL;
	exec->args = NULL;
	exec->cmd_count = 0;
	exec->fd_infile = -1;
	exec->fd_outfile = -1;
	exec->pid_child = NULL;
	exec->fd = ft_calloc(1, sizeof(t_fd));
	if (!exec->fd)
		return ;
	exec->fd->fd1[0] = -1;
	exec->fd->fd1[1] = -1;
	exec->fd->fd2[0] = -1;
	exec->fd->fd2[1] = -1;
}

void	start_exec(t_input *input)
{
	t_exec	exec;

	init_t_exec(&exec);
	print_exec(&exec, "START_EXEC");
	if (execute_all_commands(input, &exec) == 1)
	{
		free(exec.fd);
		exit_minishell(input, input->last_exit_status);
	}
	free(exec.fd);
}
